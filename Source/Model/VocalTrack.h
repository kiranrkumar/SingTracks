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
    
    String getDisplayName();

private:
    AudioBuffer<float> mBuffer;
    String mDisplayName;
    float mPanLevel;
    float mGain;
    VocalBus mBus;
};
