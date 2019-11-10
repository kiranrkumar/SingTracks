//
//  TrackGenerator.hpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/28/19.
//

#ifndef TrackGenerator_hpp
#define TrackGenerator_hpp

#include <stdio.h>

#include "../JuceLibraryCode/JuceHeader.h"

#define RUN_UNIT_TESTS 0

class TrackGenerator {
public:
    TrackGenerator();
    ~TrackGenerator();
    bool getMidiDataFromFile(File&);
    void setMidiFile(MidiFile*);
    MidiFile* getMidiFile() const;
    
    void printSummary();
private:
    MidiFile* mMidiFile;
};

class MIDIReadTest : public UnitTest
{
public:
    MIDIReadTest() : UnitTest ("Read a valid MIDI file") {}
    
    void runTest() override;
    
    void setUp();
    bool readMIDIFile();
    bool getNumTracks();
    
private:
    TrackGenerator mTrackGenerator;
};

#endif /* TrackGenerator_hpp */
