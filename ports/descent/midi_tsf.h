#pragma once

#include <stdint.h>

#include "platform/s_midi.h"

struct tsf;

class MidiTinySoundFont : public MidiSynth
{
    tsf *soundfont;
    uint32_t sample_rate;
    bool ready;

public:
    MidiTinySoundFont();
    ~MidiTinySoundFont() override;

    bool IsReady() const;

    int ClassifySynth() override;
    void SetSampleRate(uint32_t new_sample_rate) override;
    void CreateSynth() override;
    void DoMidiEvent(midievent_t *event) override;
    void RenderMIDI(int samples, unsigned short *buffer) override;
    void StopSound() override;
    void Shutdown() override;
    void SetDefaults() override;
    void PerformBranchResets(BranchEntry *entry, int channel) override;
    void SetVolume(int volume) override;
};
