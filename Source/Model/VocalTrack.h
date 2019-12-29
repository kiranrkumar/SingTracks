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
    void initializeBuffer(const MidiFile& midiFile, int trackNum);
    void renderMidiTrack(const MidiMessageSequence &track, AudioBuffer<float> &outputBuffer);
    
    AudioBuffer<float> mBuffer;
    Synthesiser mSynth;
    
    String mDisplayName;
    float mPanLevel;
    float mGain;
    VocalBus mBus;
};
