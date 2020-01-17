/*
  ==============================================================================

    TrackGenerator_TEST.cpp
    Created: 15 Dec 2019 9:07:02pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TrackGenerator_TEST.h"
#include "UnitTestDefines.h"

TrackGeneratorTest::TrackGeneratorTest() : UnitTest ("Test rendering midi tracks to audio data") {}

TrackGeneratorTest::~TrackGeneratorTest() {}

void TrackGeneratorTest::initialise() {
    mTrackGenerator.reset(new TrackGenerator());
}

void TrackGeneratorTest::runTest() {
    beginTest("readMidiFromFile");
    expect(readMidiFromFile(), String("Could not read sample MIDI file data"));
    
    beginTest("test_defaultSampleRateIsPositive()");
    expect(test_defaultSampleRateIsPositive());
}

void TrackGeneratorTest::shutdown() {
    mTrackGenerator.reset();
}

bool TrackGeneratorTest::test_defaultSampleRateIsPositive() {
    return mTrackGenerator->getSampleRate() > 0;
}

bool TrackGeneratorTest::readMidiFromFile() {
    const String midiFilePath(MIDI_FILEPATH);
    File file(midiFilePath);
    return mTrackGenerator.get()->readMidiDataFromFile(file);
}
