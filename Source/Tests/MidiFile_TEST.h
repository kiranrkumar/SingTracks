/*
  ==============================================================================

    MidiFile_TEST.h
    Created: 3 Dec 2019 8:45:00pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../Controllers/TrackGenerator.hpp"

class MIDIReadTest : public UnitTest
{
public:
    MIDIReadTest();
    ~MIDIReadTest();
    
    void initialise() override;
    void runTest() override;
    void shutdown() override;
    
    bool readMIDIFile();
    bool getNumTracks();
    
private:
    std::unique_ptr<TrackGenerator> mTrackGenerator;
};
