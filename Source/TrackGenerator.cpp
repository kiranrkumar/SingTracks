//
//  TrackGenerator.cpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/28/19.
//

#include "TrackGenerator.hpp"

#define MIDI_FILEPATH "/Users/kirankumar/SingTracks/Builds/MacOSX/OnlyLove.mid"

static bool isRelevantMidiEvent(MidiMessage &midiMessage) {
    if (!midiMessage.isNoteOn()) {
        return false;
    }
    
    return true;
}

TrackGenerator::TrackGenerator() {
    mMidiFile = new MidiFile();
}

TrackGenerator::~TrackGenerator() {
    delete mMidiFile;
}

bool TrackGenerator::getMidiDataFromFile(File& file) {
    FileInputStream inStream(file);
    return mMidiFile->readFrom(inStream);
}

void TrackGenerator::setMidiFile(MidiFile* midiFile) {
    if (mMidiFile != midiFile) {
        mMidiFile = midiFile;
    }
}

MidiFile* TrackGenerator::getMidiFile() const {
    return mMidiFile;
}

void TrackGenerator::printSummary() {
    printf("Num tracks: %d\n", mMidiFile->getNumTracks());
    printf("Time format: %d\n", mMidiFile->getTimeFormat());
    
    mMidiFile->convertTimestampTicksToSeconds();
    for (int i = 0; i < mMidiFile->getNumTracks(); ++i) {
        const MidiMessageSequence *track = mMidiFile->getTrack(i);
        printf("\t%d: %d events\n", i, track->getNumEvents());
        for (MidiMessageSequence::MidiEventHolder* const* iterator = track->begin(); iterator != track->end(); ++iterator) {
            MidiMessage message = (*iterator)->message;
            if (isRelevantMidiEvent(message)) {
                printf("\t\t%4.2f: %s\n", message.getTimeStamp(), MidiMessage::getMidiNoteName(message.getNoteNumber(), true, true, 3).toStdString().c_str());
            }
        }
    }
}

#pragma mark - MIDIReadTest
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
