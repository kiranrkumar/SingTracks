/*
  ==============================================================================

    VocalTrack.h
    Created: 27 Dec 2019 5:21:33pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

typedef enum {
    Solo,
    Background
} VocalBus;

class VocalTrack {
public:
    VocalTrack(const MidiFile &midiFile, int trackNum);
    ~VocalTrack();

private:
    AudioBuffer<float> mBuffer;
    float mPanLevel;
    float mGain;
    VocalBus mBus;
};
