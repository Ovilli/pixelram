/*
 * TinySoundFont MIDI backend for Chocolate Descent / WebAssembly.
 *
 * Chocolate Descent already parses its original HMP music files and exposes
 * the resulting MIDI events through MidiSequencer. This class only turns
 * those events into PCM.
 */

#include "midi_tsf.h"

#include <stdio.h>

#define TSF_IMPLEMENTATION
#include "tsf.h"

static const char *SOUNDFONT_PATH = "/TimGM6mb.sf2";

MidiTinySoundFont::MidiTinySoundFont()
    : soundfont(nullptr),
      sample_rate(MIDI_SAMPLERATE),
      ready(false)
{
}

MidiTinySoundFont::~MidiTinySoundFont()
{
    Shutdown();
}

bool MidiTinySoundFont::IsReady() const
{
    return ready;
}

int MidiTinySoundFont::ClassifySynth()
{
    return MIDISYNTH_SOFT;
}

void MidiTinySoundFont::SetSampleRate(uint32_t new_sample_rate)
{
    sample_rate = new_sample_rate;
}

void MidiTinySoundFont::CreateSynth()
{
    if (soundfont)
        return;

    soundfont = tsf_load_filename(SOUNDFONT_PATH);

    if (!soundfont)
    {
        fprintf(
            stderr,
            "Could not load MIDI SoundFont: %s\n",
            SOUNDFONT_PATH
        );
        ready = false;
        return;
    }

    tsf_set_output(
        soundfont,
        TSF_STEREO_INTERLEAVED,
        (int)sample_rate,
        -6.0f
    );

    tsf_set_max_voices(soundfont, 128);

    ready = true;
    SetDefaults();
}

void MidiTinySoundFont::Shutdown()
{
    if (!soundfont)
        return;

    tsf_close(soundfont);
    soundfont = nullptr;
    ready = false;
}

void MidiTinySoundFont::SetDefaults()
{
    if (!soundfont)
        return;

    tsf_reset(soundfont);

    /*
     * Match Chocolate Descent's FluidSynth defaults closely: HMI songs
     * initially own the channel volume and program state.
     */
    for (int channel = 0; channel < 16; channel++)
    {
        tsf_channel_set_presetnumber(
            soundfont,
            channel,
            0,
            channel == 9
        );

        tsf_channel_set_pitchwheel(
            soundfont,
            channel,
            8192
        );

        tsf_channel_midi_control(
            soundfont,
            channel,
            7,
            0
        );

        tsf_channel_midi_control(
            soundfont,
            channel,
            39,
            0
        );
    }
}

void MidiTinySoundFont::DoMidiEvent(midievent_t *event)
{
    if (!soundfont || !event)
        return;

    const int channel = event->GetChannel();

    switch (event->GetType())
    {
        case EVENT_NOTEON:
            if (event->param2 == 0)
            {
                tsf_channel_note_off(
                    soundfont,
                    channel,
                    event->param1
                );
            }
            else
            {
                tsf_channel_note_on(
                    soundfont,
                    channel,
                    event->param1,
                    event->param2 / 127.0f
                );
            }
            break;

        case EVENT_NOTEOFF:
            tsf_channel_note_off(
                soundfont,
                channel,
                event->param1
            );
            break;

        case EVENT_CONTROLLER:
            tsf_channel_midi_control(
                soundfont,
                channel,
                event->param1,
                event->param2
            );
            break;

        case EVENT_PATCH:
            tsf_channel_set_presetnumber(
                soundfont,
                channel,
                event->param1,
                channel == 9
            );
            break;

        case EVENT_PITCH:
            tsf_channel_set_pitchwheel(
                soundfont,
                channel,
                event->param1 + (event->param2 << 7)
            );
            break;

        /*
         * TinySoundFont's channel API has no aftertouch equivalent.
         * Descent's soundtrack does not depend on it for normal playback.
         */
        case EVENT_AFTERTOUCH:
        case EVENT_PRESSURE:
        default:
            break;
    }
}

void MidiTinySoundFont::RenderMIDI(
    int samples,
    unsigned short *buffer)
{
    if (!soundfont || !buffer || samples <= 0)
        return;

    tsf_render_short(
        soundfont,
        (short *)buffer,
        samples,
        0
    );
}

void MidiTinySoundFont::StopSound()
{
    if (!soundfont)
        return;

    for (int channel = 0; channel < 16; channel++)
    {
        tsf_channel_sounds_off_all(
            soundfont,
            channel
        );
    }
}

void MidiTinySoundFont::PerformBranchResets(
    BranchEntry *entry,
    int channel)
{
    if (!soundfont || !entry)
        return;

    for (int i = 0; i < entry->controlChangeCount; i++)
    {
        tsf_channel_midi_control(
            soundfont,
            channel,
            entry->controlChanges[i].controller,
            entry->controlChanges[i].state
        );
    }
}

void MidiTinySoundFont::SetVolume(int volume)
{
    /*
     * The OpenAL streaming source applies Chocolate Descent's music volume.
     * Keep the synth gain fixed so volume is not applied twice.
     */
    (void)volume;
}
