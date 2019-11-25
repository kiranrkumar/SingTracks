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

#pragma mark - MIDITrackSynthesizerSound
bool MIDITrackSynthesizerSound::appliesToNote(int midiNoteNumber)
{
    return true;
}

bool MIDITrackSynthesizerSound::appliesToChannel(int midiChannel)
{
    // KRK_FIXME - fix once I know which channels to allow
    return false;
}

#pragma mark - MIDITrackSynthesizerVoice
bool MIDITrackSynthesizerVoice::canPlaySound(SynthesiserSound *synthSound)
{
    return true;
}

void MIDITrackSynthesizerVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    // KRK_FIXME - to do
}

void MIDITrackSynthesizerVoice::stopNote (float velocity, bool allowTailOff)
{
    // KRK_FIXME - to do
}

void MIDITrackSynthesizerVoice::pitchWheelMoved (int newPitchWheelValue)
{
    // KRK_FIXME - to do
}

void MIDITrackSynthesizerVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    // KRK_FIXME - to do
}
void MIDITrackSynthesizerVoice::renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    // KRK_FIXME - to do
}

#pragma mark - TrackGenerator
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
