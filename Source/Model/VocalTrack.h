/*
  ==============================================================================

    VocalTrack.h
    Created: 27 Dec 2019 5:21:33pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AudioDefines.h"

class VocalTrack {
public:
    VocalTrack(const MidiFile &midiFile, int trackNum);
    
    String getDisplayName();
    VocalBus getBus();
    void setBus(VocalBus bus);
    const AudioBuffer<float>& getBuffer() const;
    AudioBuffer<float> getBufferCopy();

private:
    void initializeBuffer(const MidiFile& midiFile, int trackNum);
    void renderMidiTrack(const MidiFile& midiFile, int trackNum);
    
    AudioBuffer<float> mBuffer;
    Synthesiser mSynth;
    
    String mDisplayName;
    VocalBus mBus; // Maybe have some change notifications to broadcast from the TrackSettingsComponent to these vocal tracks to change the busses
};
