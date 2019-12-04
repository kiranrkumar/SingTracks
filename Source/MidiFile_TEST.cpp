/*
  ==============================================================================

    MidiFile_TEST.cpp
    Created: 3 Dec 2019 8:45:00pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "MidiFile_TEST.h"

#define MIDI_FILEPATH "/Users/kirankumar/SingTracks/Builds/MacOSX/OnlyLove.mid"

void MIDIReadTest::setUp()
{
    // no-op?
}

void MIDIReadTest::runTest()
{
    beginTest("Part 1");
    expect(readMIDIFile(), String("Cannot read MIDI file successfully"));

    beginTest("Part 2");
    expect(getNumTracks(), String("Cannot get num tracks from MIDI file"));
}

bool MIDIReadTest::readMIDIFile()
{
    File file(MIDI_FILEPATH);
    return mTrackGenerator.getMidiDataFromFile(file);
}

bool MIDIReadTest::getNumTracks()
{
    return (mTrackGenerator.getMidiFile()->getNumTracks() > 0);
}

#pragma mark - FileWriteTest

void FileWriteTest::runTest()
{
    
}

void FileWriteTest::setUp()
{
    
}

bool FileWriteTest::createFileObject(String)
{
    File dir = File::getSpecialLocation(File::userDocumentsDirectory);
    mFileObject = dir.getNonexistentChildFile("FileWriteUnitTest", ".wav");
    
    return true;
}

bool FileWriteTest::writeFileToDisk()
{
    mBackgroundThread.startThread();
    
    return false;
}
