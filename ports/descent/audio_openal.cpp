/*
 * Digital sound-effects backend for Chocolate Descent on WebAssembly.
 *
 * Music is deliberately disabled for this milestone; the browser build
 * starts with -nomusic. Emscripten supplies OpenAL over Web Audio.
 */

#include "platform/i_sound.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#include <cmath>
#include <cstdint>
#include <vector>

static ALCdevice *device = nullptr;
static ALCcontext *context = nullptr;
static ALuint buffers[_MAX_VOICES];
static ALuint sources[_MAX_VOICES];
static bool ready = false;

static bool valid(int handle)
{
    return handle >= 0 && handle < _MAX_VOICES;
}

static void reset_source(int handle)
{
    if (!valid(handle))
        return;

    alSourceStop(sources[handle]);
    alSourcei(sources[handle], AL_BUFFER, 0);
    alSourcei(sources[handle], AL_LOOPING, AL_FALSE);
    alSourcef(sources[handle], AL_GAIN, 1.0f);
    alSourcef(sources[handle], AL_PITCH, 1.0f);
    alSourcef(sources[handle], AL_ROLLOFF_FACTOR, 0.0f);
    alSource3f(sources[handle], AL_POSITION, 0.0f, 0.0f, -1.0f);
}

int plat_init_audio()
{
    if (ready)
        return 0;

    device = alcOpenDevice(nullptr);
    if (!device)
        return 1;

    context = alcCreateContext(device, nullptr);
    if (!context)
    {
        alcCloseDevice(device);
        device = nullptr;
        return 1;
    }

    if (!alcMakeContextCurrent(context))
    {
        alcDestroyContext(context);
        alcCloseDevice(device);
        context = nullptr;
        device = nullptr;
        return 1;
    }

    alGenBuffers(_MAX_VOICES, buffers);
    alGenSources(_MAX_VOICES, sources);

    for (int i = 0; i < _MAX_VOICES; ++i)
        reset_source(i);

    ready = true;
    return 0;
}

void plat_close_audio()
{
    if (!ready)
        return;

    for (int i = 0; i < _MAX_VOICES; ++i)
        alSourceStop(sources[i]);

    alDeleteSources(_MAX_VOICES, sources);
    alDeleteBuffers(_MAX_VOICES, buffers);

    alcMakeContextCurrent(nullptr);

    if (context)
        alcDestroyContext(context);

    if (device)
        alcCloseDevice(device);

    context = nullptr;
    device = nullptr;
    ready = false;
}

int plat_get_new_sound_handle()
{
    if (!ready)
        return _ERR_NO_SLOTS;

    for (int i = 0; i < _MAX_VOICES; ++i)
    {
        ALint state = 0;
        alGetSourcei(sources[i], AL_SOURCE_STATE, &state);

        if (state != AL_PLAYING && state != AL_PAUSED)
        {
            reset_source(i);
            return i;
        }
    }

    return _ERR_NO_SLOTS;
}

void plat_set_sound_data(
    int handle,
    unsigned char *data,
    int length,
    int sample_rate)
{
    if (!ready || !valid(handle) || !data || length <= 0)
        return;

    alSourcei(sources[handle], AL_BUFFER, 0);

    alBufferData(
        buffers[handle],
        AL_FORMAT_MONO8,
        data,
        length,
        sample_rate
    );
}

void plat_set_sound_position(int handle, int volume, int angle)
{
    plat_set_sound_volume(handle, volume);
    plat_set_sound_angle(handle, angle);
}

void plat_set_sound_angle(int handle, int angle)
{
    if (!ready || !valid(handle))
        return;

    const float radians =
        (float)angle *
        (2.0f * 3.14159265358979323846f / 65536.0f);

    const float x = std::sin(radians);

    alSource3f(
        sources[handle],
        AL_POSITION,
        x,
        0.0f,
        -1.0f
    );
}

void plat_set_sound_volume(int handle, int volume)
{
    if (!ready || !valid(handle))
        return;

    float gain = (float)volume / 32768.0f;

    if (gain < 0.0f) gain = 0.0f;
    if (gain > 1.0f) gain = 1.0f;

    alSourcef(sources[handle], AL_GAIN, gain);
}

void plat_set_sound_loop_points(int handle, int start, int end)
{
    if (!ready || !valid(handle))
        return;

#ifdef AL_LOOP_POINTS_SOFT
    if (start >= 0 && end > start)
    {
        ALint points[2] = { start, end };

        alBufferiv(
            buffers[handle],
            AL_LOOP_POINTS_SOFT,
            points
        );
    }
#else
    (void)start;
    (void)end;
#endif
}

void plat_start_sound(int handle, int loop)
{
    if (!ready || !valid(handle))
        return;

    alSourcei(
        sources[handle],
        AL_BUFFER,
        buffers[handle]
    );

    alSourcei(
        sources[handle],
        AL_LOOPING,
        loop ? AL_TRUE : AL_FALSE
    );

    alSourcePlay(sources[handle]);
}

void plat_stop_sound(int handle)
{
    if (!ready || !valid(handle))
        return;

    alSourceStop(sources[handle]);
}

int plat_check_if_sound_playing(int handle)
{
    if (!ready || !valid(handle))
        return 0;

    ALint state = 0;
    alGetSourcei(sources[handle], AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

int plat_check_if_sound_finished(int handle)
{
    if (!ready || !valid(handle))
        return 1;

    ALint state = 0;
    alGetSourcei(sources[handle], AL_SOURCE_STATE, &state);

    return state != AL_PLAYING && state != AL_PAUSED;
}

/* --------------------------------------------------------------------- */
/* Streaming MIDI music                                                  */
/* --------------------------------------------------------------------- */

#define MUSIC_BUFFER_COUNT 6

struct WebMusicSource
{
    ALuint source;
    ALuint buffers[MUSIC_BUFFER_COUNT];
    bool buffer_free[MUSIC_BUFFER_COUNT];
    uint32_t sample_rate;
};

static int music_volume = 127;

static void clear_music_queue(WebMusicSource *music)
{
    if (!music)
        return;

    alSourceStop(music->source);

    ALint queued = 0;
    alGetSourcei(
        music->source,
        AL_BUFFERS_QUEUED,
        &queued
    );

    while (queued > 0)
    {
        ALuint buffer = 0;

        alSourceUnqueueBuffers(
            music->source,
            1,
            &buffer
        );

        for (int i = 0; i < MUSIC_BUFFER_COUNT; i++)
        {
            if (music->buffers[i] == buffer)
            {
                music->buffer_free[i] = true;
                break;
            }
        }

        queued--;
    }
}

int plat_start_midi(MidiSequencer *)
{
    return ready ? 0 : 1;
}

uint32_t plat_get_preferred_midi_sample_rate()
{
    return MIDI_SAMPLERATE;
}

void plat_close_midi()
{
}

void plat_set_music_volume(int volume)
{
    if (volume < 0)
        volume = 0;

    if (volume > 127)
        volume = 127;

    music_volume = volume;
}

void plat_start_midi_song(HMPFile *, bool)
{
}

void plat_stop_midi_song()
{
}

void *midi_start_source()
{
    if (!ready)
        return nullptr;

    WebMusicSource *music =
        new WebMusicSource();

    music->sample_rate =
        MIDI_SAMPLERATE;

    alGenSources(
        1,
        &music->source
    );

    alSourcef(
        music->source,
        AL_ROLLOFF_FACTOR,
        0.0f
    );

    alSource3f(
        music->source,
        AL_POSITION,
        0.0f,
        0.0f,
        0.0f
    );

    alSourcef(
        music->source,
        AL_GAIN,
        music_volume / 127.0f
    );

    alGenBuffers(
        MUSIC_BUFFER_COUNT,
        music->buffers
    );

    for (int i = 0; i < MUSIC_BUFFER_COUNT; i++)
        music->buffer_free[i] = true;

    return music;
}

void midi_stop_source(void *opaque_source)
{
    WebMusicSource *music =
        (WebMusicSource *)opaque_source;

    if (!music)
        return;

    clear_music_queue(music);

    alDeleteSources(
        1,
        &music->source
    );

    alDeleteBuffers(
        MUSIC_BUFFER_COUNT,
        music->buffers
    );

    delete music;
}

void midi_set_music_samplerate(
    void *opaque_source,
    uint32_t sample_rate)
{
    WebMusicSource *music =
        (WebMusicSource *)opaque_source;

    if (!music)
        return;

    music->sample_rate = sample_rate;
}

void midi_dequeue_midi_buffers(void *opaque_source)
{
    WebMusicSource *music =
        (WebMusicSource *)opaque_source;

    if (!music)
        return;

    ALint processed = 0;

    alGetSourcei(
        music->source,
        AL_BUFFERS_PROCESSED,
        &processed
    );

    while (processed > 0)
    {
        ALuint buffer = 0;

        alSourceUnqueueBuffers(
            music->source,
            1,
            &buffer
        );

        for (int i = 0; i < MUSIC_BUFFER_COUNT; i++)
        {
            if (music->buffers[i] == buffer)
            {
                music->buffer_free[i] = true;
                break;
            }
        }

        processed--;
    }

    alSourcef(
        music->source,
        AL_GAIN,
        music_volume / 127.0f
    );
}

bool midi_queue_slots_available(void *opaque_source)
{
    WebMusicSource *music =
        (WebMusicSource *)opaque_source;

    if (!music)
        return false;

    for (int i = 0; i < MUSIC_BUFFER_COUNT; i++)
    {
        if (music->buffer_free[i])
            return true;
    }

    return false;
}

void midi_queue_buffer(
    void *opaque_source,
    int sample_frames,
    uint16_t *data)
{
    WebMusicSource *music =
        (WebMusicSource *)opaque_source;

    if (!music || !data || sample_frames <= 0)
        return;

    int slot = -1;

    for (int i = 0; i < MUSIC_BUFFER_COUNT; i++)
    {
        if (music->buffer_free[i])
        {
            slot = i;
            break;
        }
    }

    if (slot < 0)
        return;

    music->buffer_free[slot] = false;

    alBufferData(
        music->buffers[slot],
        AL_FORMAT_STEREO16,
        data,
        sample_frames *
            2 *
            (int)sizeof(int16_t),
        music->sample_rate
    );

    alSourceQueueBuffers(
        music->source,
        1,
        &music->buffers[slot]
    );
}

void midi_check_status(void *opaque_source)
{
    WebMusicSource *music =
        (WebMusicSource *)opaque_source;

    if (!music)
        return;

    ALint queued = 0;
    ALint state = 0;

    alGetSourcei(
        music->source,
        AL_BUFFERS_QUEUED,
        &queued
    );

    if (queued == 0)
        return;

    alGetSourcei(
        music->source,
        AL_SOURCE_STATE,
        &state
    );

    if (state != AL_PLAYING)
        alSourcePlay(music->source);
}

bool midi_check_finished(void *opaque_source)
{
    WebMusicSource *music =
        (WebMusicSource *)opaque_source;

    if (!music)
        return true;

    ALint queued = 0;
    ALint state = 0;

    alGetSourcei(
        music->source,
        AL_BUFFERS_QUEUED,
        &queued
    );

    alGetSourcei(
        music->source,
        AL_SOURCE_STATE,
        &state
    );

    return
        queued == 0 &&
        state != AL_PLAYING;
}

/* HQ music is not used by the original Descent 1 MIDI soundtrack. */

void plat_start_hq_song(
    int,
    std::vector<float> &&,
    bool)
{
}

void plat_stop_hq_song()
{
}


/* Movie audio is unused by normal Descent 1 gameplay. */

void mvesnd_init_audio(int, int, int) {}
void mvesnd_queue_audio_buffer(int, short *) {}
void mvesnd_close() {}
void mvesnd_pause() {}
void mvesnd_resume() {}
