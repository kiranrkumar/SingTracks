/*
  ==============================================================================

    TrackGenerator_TEST.h
    Created: 15 Dec 2019 9:07:02pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "TrackGenerator.hpp"

class TrackGeneratorTest : public UnitTest
{
public:
    TrackGeneratorTest() : UnitTest ("Test rendering midi tracks to audio data") {}
    ~TrackGeneratorTest();
    
    void runTest() override;
    
private:
    bool readMidiFromFile();
    
    TrackGenerator mTrackGenerator;
    MidiFile mMidiFile;
};
