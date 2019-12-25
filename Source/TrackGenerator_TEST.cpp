/*
  ==============================================================================

    TrackGenerator_TEST.cpp
    Created: 15 Dec 2019 9:07:02pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TrackGenerator_TEST.h"

void TrackGeneratorTest::initialise() {
    mTrackGenerator.reset(new TrackGenerator());
}

void TrackGeneratorTest::runTest() {
    beginTest("readMidiFromFile");
    expect(readMidiFromFile(), String("Could not read sample MIDI file data"));
}

void TrackGeneratorTest::shutdown() {
    mTrackGenerator.reset();
}

bool TrackGeneratorTest::readMidiFromFile() {
    const String midiFilePath("~/SingTracks/Builds/MacOSX/twoTrackScale.mid"); // KRK_FIXME unstable file path!
    File file(midiFilePath);
    return mTrackGenerator.get()->readMidiDataFromFile(file);
}
