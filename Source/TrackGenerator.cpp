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

static float getSineSample()
{
    static float alpha = 0;
    const float twoPi = 2 * M_PI;
    alpha += (twoPi * 340  / 48000);
    if (alpha > twoPi) {
        alpha -= twoPi;
    }
    
    float sample = std::sin(alpha);
    return sample;
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
    mMidiFile->convertTimestampTicksToSeconds();
    DEBUG_LOG("Num tracks: %d\n", mMidiFile->getNumTracks());
    DEBUG_LOG("Time format: %d\n", mMidiFile->getTimeFormat());
}

void TrackGenerator::renderMidiToAudio()
{
    int numTracks = mMidiFile->getNumTracks();
    int numSamples = int(ceil(mMidiFile->getLastTimestamp() * mSampleRate));
    DEBUG_LOG("%d tracks\n", numTracks);
    
    AudioBuffer<float> outputBuffer;
    outputBuffer.setSize(1, numSamples);
    outputBuffer.clear();
    
    const int BLOCKSIZE = 256;

    for (int i = 0; i < mMidiFile->getNumTracks(); ++i) {
        const MidiMessageSequence *track = mMidiFile->getTrack(i);
        int numMidiEventsInTrack = track->getNumEvents();
        DEBUG_LOG("\t%d: %d events\n", i, numMidiEventsInTrack);
        
        int startIndex = 0;
        int currentBufferLength = std::min(numSamples - startIndex - 1, BLOCKSIZE);
        
        int midiEventIndex = 0;
        MidiBuffer midiBuffer; // placeholder. noteOn() and noteOff() messages will be called manually
        
        while (startIndex < numSamples) {
            midiBuffer.clear();
            
            float startTime = (float)startIndex / mSampleRate;
            float endTime = startTime + (float)currentBufferLength / mSampleRate;
//            DEBUG_LOG("\t\t%.2f - %.2f\n", startTime, endTime);
            
            MidiMessage message = track->getEventPointer(midiEventIndex)->message;
            while (message.getTimeStamp() < endTime && midiEventIndex < numMidiEventsInTrack) {
                DEBUG_LOG("\t\t\tAdding Midi event %s\n", message.getDescription().toRawUTF8());
                midiEventIndex++;
                midiBuffer.addEvent(message, startIndex);
                if (message.isNoteOn()) {
                    DEBUG_LOG("Note On | Start Ix: %d | Buffer Len: %d\n", startIndex, currentBufferLength);
                }
                else if (message.isNoteOff()) {
                    DEBUG_LOG("Note Off | Start Ix: %d | Buffer Len: %d\n", startIndex, currentBufferLength);
                }
                
                if (midiEventIndex < numMidiEventsInTrack) {
                    message = track->getEventPointer(midiEventIndex)->message;
                }
            }
            
            mSynth.renderNextBlock(outputBuffer, midiBuffer, startIndex, currentBufferLength);
            
            startIndex += BLOCKSIZE;
            currentBufferLength = std::min(numSamples - startIndex - 1, BLOCKSIZE);
            
        }
        
        // print buffer just to see
        for (int i = 0; i < numSamples; i += 100) {
            DEBUG_LOG("%.2f,", outputBuffer.getSample(0, i));
        }
    }
    
    DEBUG_LOG("\n");
    
    writeAudioToFile(outputBuffer);
}

bool TrackGenerator::writeAudioToFile(AudioBuffer<float>& buffer)
{
    DEBUG_LOG("Writing audio to file...\n");
    File outFile("~/audioTestFile.wav");
    FileOutputStream *outStream = new FileOutputStream(outFile);
    if (outStream->openedOk()) {
        outStream->setPosition(0);
        outStream->truncate();
    }
    
    AudioFormatManager manager;
    manager.registerBasicFormats();
    
    WavAudioFormat wavFormat;
    std::unique_ptr<AudioFormatWriter> writer(wavFormat.createWriterFor(outStream, mSampleRate, 1, 16, {}, 0));
    
    DEBUG_LOG("Writing %d samples\n", buffer.getNumSamples());
    writer.get()->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    
    return true;
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
