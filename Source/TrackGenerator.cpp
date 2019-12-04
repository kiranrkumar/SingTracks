//
//  TrackGenerator.cpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/28/19.
//

#include "TrackGenerator.hpp"
#include "MIDITrackSynthesizer.h"

const int NUM_OUTPUT_CHANNELS = 2;

TrackGenerator::TrackGenerator() {
    mMidiFile = new MidiFile();
    
    mSampleRate = 48000;
    
    mSynth.clearVoices();
    for (int i = 0; i < 10; ++i) {
        mSynth.addVoice(new MIDITrackSynthesizerVoice());
    }
    
    mSynth.clearSounds();
    mSynth.addSound(new MIDITrackSynthesizerSound());
    mSynth.setCurrentPlaybackSampleRate(mSampleRate);
}

TrackGenerator::~TrackGenerator() {
    delete mMidiFile;
    mSynth.clearVoices();
    mSynth.clearSounds();
}

bool TrackGenerator::getMidiDataFromFile(File& file) {
    FileInputStream inStream(file);
    return mMidiFile->readFrom(inStream);
}

void TrackGenerator::setMidiFile(MidiFile* midiFile) {
    if (mMidiFile != midiFile) {
        delete mMidiFile;
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

    // KRK_FIXME there has to be a better way to do this, but for some MIDIs created in Logic
    //  (particularly ones that are more than one track), there's an extra first track that
    //  contains all of the initial "global" metadata (time signature, key signature, etc) plus a
    //  track-end event with a LARGE timestamp that's causing the program to render
    //  way too many samples.
    //
    // This (hopefully temporary) fix searches all tracks for the last "note off" event
    //  and grabs the timestamp from that.
double TrackGenerator::getTrueLastTimestamp(MidiFile* midiFile)
{
    double lastTimeStamp = 0;
    int numTracks = midiFile->getNumTracks();
    
    for (int trackIndex = 0; trackIndex < numTracks; ++trackIndex) {
        const MidiMessageSequence *track = mMidiFile->getTrack(trackIndex);
        int numEvents = track->getNumEvents();
        for (int midiEventIndex = numEvents - 1; midiEventIndex >= 0; midiEventIndex--) {
            MidiMessage message = track->getEventPointer(midiEventIndex)->message;
            if (message.isNoteOff()) {
                lastTimeStamp = std::max(lastTimeStamp, message.getTimeStamp());
                continue;
            }
        }
    }
    
    return lastTimeStamp;
}

void TrackGenerator::normalizeBuffer(AudioBuffer<float>& buffer, float maxMagnitude)
{
    int numSamples = buffer.getNumSamples();
    float trueMaxMag = std::min(maxMagnitude, 1.f);
    buffer.applyGain(0, numSamples, trueMaxMag / buffer.getMagnitude(0, numSamples));
}

void TrackGenerator::renderMidiToAudio()
{
    int numTracks = mMidiFile->getNumTracks();
    DEBUG_LOG("%d tracks\n", numTracks);
    double lastTimeStamp = getTrueLastTimestamp(mMidiFile);
    int numSamples = int(ceil(lastTimeStamp * mSampleRate));
    
    AudioBuffer<float> outputBuffer;
    outputBuffer.setSize(NUM_OUTPUT_CHANNELS, numSamples);
    outputBuffer.clear();

    for (int i = 0; i < mMidiFile->getNumTracks(); ++i) {
        const MidiMessageSequence *track = mMidiFile->getTrack(i);
        int numMidiEventsInTrack = track->getNumEvents();
        DEBUG_LOG("\t%d: %d events\n", i, numMidiEventsInTrack);
        
        const int BLOCKSIZE = 256;
        int startIndex = 0;
        int currentBufferLength = std::min(numSamples - startIndex, BLOCKSIZE);
        int midiEventIndex = 0;
        
        MidiBuffer midiBuffer;
        
        while (startIndex < numSamples && midiEventIndex < numMidiEventsInTrack) {
            midiBuffer.clear();
            float startTime = (float)startIndex / mSampleRate;
            float endTime = startTime + (float)currentBufferLength / mSampleRate;
            
            MidiMessage message = track->getEventPointer(midiEventIndex)->message;

            while (message.getTimeStamp() < endTime && midiEventIndex < numMidiEventsInTrack) {
                DEBUG_LOG("\t\t\tAdding Midi event %s\n", message.getDescription().toRawUTF8());
                midiBuffer.addEvent(message, startIndex);
                if (message.isNoteOn()) {
                    DEBUG_LOG("Note On | Start Ix: %d | Buffer Len: %d\n", startIndex, currentBufferLength);
//                    mSynth.noteOn(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
                }
                else if (message.isNoteOff()) {
                    DEBUG_LOG("Note Off | Start Ix: %d | Buffer Len: %d\n", startIndex, currentBufferLength);
//                    mSynth.noteOff(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity(), true);
                }
                
                if (++midiEventIndex < numMidiEventsInTrack) {
                    message = track->getEventPointer(midiEventIndex)->message;
                }
            }
            
            mSynth.renderNextBlock(outputBuffer, midiBuffer, startIndex, currentBufferLength);
            
            startIndex += BLOCKSIZE;
            currentBufferLength = std::min(numSamples - startIndex - 1, BLOCKSIZE);
        }
    }
    
    DEBUG_LOG("\n");
    
    normalizeBuffer(outputBuffer, 0.85);
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
    std::unique_ptr<AudioFormatWriter> writer(wavFormat.createWriterFor(outStream, mSampleRate, NUM_OUTPUT_CHANNELS, 16, {}, 0));
    
    DEBUG_LOG("Writing %d samples\n", buffer.getNumSamples());
    writer.get()->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    
    return true;
}
