//
//  TrackGenerator.cpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/28/19.
//

#include "TrackGenerator.hpp"
#include "MIDITrackSynthesizer.h"

#define MIDI_FILEPATH "/Users/kirankumar/SingTracks/Builds/MacOSX/OnlyLove.mid"
#define USE_NOTES_ONLY 1

static bool isRelevantMidiEvent(MidiMessage &midiMessage) {
    
#if USE_NOTES_ONLY
    if (!midiMessage.isNoteOn() && !midiMessage.isNoteOff()) {
        return false;
    }
#endif
    
    return true;
}

TrackGenerator::TrackGenerator() {
    mMidiFile = new MidiFile();
        
    mSampleRate = 48000;
    
    mSynth.clearVoices();
    for (int i = 0; i < 1; ++i) {
        mSynth.addVoice(new MIDITrackSynthesizerVoice());
    }
    
    mSynth.clearSounds();
    mSynth.addSound(new MIDITrackSynthesizerSound());
    mSynth.setCurrentPlaybackSampleRate(mSampleRate);
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
    MidiBuffer midiBuffer;
    int midiSamplePos = 0;
    for (int i = 0; i < mMidiFile->getNumTracks(); ++i) {
        const MidiMessageSequence *track = mMidiFile->getTrack(i);
        printf("\t%d: %d events\n", i, track->getNumEvents());
        for (MidiMessageSequence::MidiEventHolder* const* iterator = track->begin(); iterator != track->end(); ++iterator) {
            MidiMessage message = (*iterator)->message;
            if (isRelevantMidiEvent(message)) {
//                printf("\t\t%4.2f sec: %s\n", message.getTimeStamp(), message.getDescription().toStdString().c_str());
                midiBuffer.addEvent(message, midiSamplePos++);
            }
        }
    }
    
    const int numChannels = 1;
    float durationInSec = .2;
    int numSamples = (int)(mSampleRate * durationInSec);
    
    AudioBuffer<float> outputBuffer(numChannels, numSamples);
    outputBuffer.clear();
    mSynth.renderNextBlock(outputBuffer, midiBuffer, 0, numSamples);
    for (int i = 0; i < numSamples; ++i) {
        for (int c = 0; c < numChannels; ++c) {
//            if (c == 0) {
//                std::cout << outputBuffer.getSample(c, i) << "|";
//            }
//            else {
//                std::cout << outputBuffer.getSample(c, i) << std::endl;
            printf("%d | %.2f\n", i, outputBuffer.getSample(c, i));
//            }
        }
    }
    
//    // Try iterating through the Midi buffer
//    MidiBuffer::Iterator midiBufferIterator(midiBuffer);
//    MidiMessage message;
//    int sample;
//
//    while (midiBufferIterator.getNextEvent(message, sample)) {
//        printf("\t\t%4.2f sec: %s\n", message.getTimeStamp(), message.getDescription().toStdString().c_str());
//        if (message.isNoteOn()) {
//            mSynth.noteOn(message.getChannel(), message.getNoteNumber(), message.getVelocity());
//        }
//        else if (message.isNoteOff()) {
//            mSynth.noteOff(message.getChannel(), message.getNoteNumber(), message.getVelocity(), true);
//        }
//    }
    
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
