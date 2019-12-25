/*
  ==============================================================================

    MidiFile_TEST.cpp
    Created: 3 Dec 2019 8:45:00pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "MidiFile_TEST.h"

const char* const MIDI_FILEPATH = "/Users/kirankumar/SingTracks/Builds/MacOSX/OnlyLove.mid";

void MIDIReadTest::initialise()
{
    mTrackGenerator.reset(new TrackGenerator());
}

void MIDIReadTest::runTest()
{
    beginTest("Part 1");
    expect(readMIDIFile(), String("Cannot read MIDI file successfully"));

    beginTest("Part 2");
    expect(getNumTracks(), String("Cannot get num tracks from MIDI file"));
}

void MIDIReadTest::shutdown()
{
    mTrackGenerator.reset();
}

bool MIDIReadTest::readMIDIFile()
{
    File file(MIDI_FILEPATH);
    return mTrackGenerator.get()->readMidiDataFromFile(file);
}

bool MIDIReadTest::getNumTracks()
{
    return (mTrackGenerator.get()->getMidiFile().getNumTracks() > 0);
}
