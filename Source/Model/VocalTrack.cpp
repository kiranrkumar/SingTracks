/*
  ==============================================================================

    VocalTrack.cpp
    Created: 27 Dec 2019 5:21:33pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "VocalTrack.h"

#include "../Controllers/MIDITrackSynthesizer.h"

const double SAMPLE_RATE = 48000;
const int NUM_OUTPUT_CHANNELS = 2;
const int NUM_SYNTH_VOICES = 10;

VocalTrack::VocalTrack(const MidiFile &midiFile, int trackNum)
{
    std::string displayName;
    displayName += "Midi track "; // KRK_TEMP
    displayName += std::to_string(trackNum);
    mDisplayName = String(displayName);
    
    // Set up synth
    mSynth.clearVoices();
    for (int i = 0; i < NUM_SYNTH_VOICES; ++i) {
        mSynth.addVoice(new MIDITrackSynthesizerVoice());
    }
    
    mSynth.clearSounds();
    mSynth.addSound(new MIDITrackSynthesizerSound());
    mSynth.setCurrentPlaybackSampleRate(SAMPLE_RATE);
    
    // Set up buffer
    initializeBuffer(midiFile, trackNum);
    renderMidiTrack(midiFile, trackNum);
}

String VocalTrack::getDisplayName()
{
    return mDisplayName;
}

void VocalTrack::initializeBuffer(const MidiFile& midiFile, int trackNum)
{
    jassert(trackNum < midiFile.getNumTracks());
    double lastTimeStamp = 0;
    const MidiMessageSequence *track = midiFile.getTrack(trackNum);
    int numEvents = track->getNumEvents();
    
    // Get the last noteOff event of the track to determine track length
    //  KRK_FIXME this doesn't account for potential tail times
    for (int midiEventIndex = numEvents - 1; midiEventIndex >= 0; midiEventIndex--) {
        MidiMessage message = track->getEventPointer(midiEventIndex)->message;
        if (message.isNoteOff()) {
            lastTimeStamp = std::max(lastTimeStamp, message.getTimeStamp());
            break;
        }
    }
    
    int numSamples = int(ceil(lastTimeStamp * SAMPLE_RATE));
    mBuffer.setSize(NUM_OUTPUT_CHANNELS, numSamples);
    mBuffer.clear();
}

void VocalTrack::renderMidiTrack(const MidiFile& midiFile, int trackNum) {
    MidiMessageSequence track = *(midiFile.getTrack(trackNum));
    const int BLOCKSIZE = 256;
    MidiBuffer midiBuffer;
    int startIndex = 0;
    int midiEventIndex = 0;
    
    int bufferNumSamples = mBuffer.getNumSamples();
    int numMidiEventsInTrack = track.getNumEvents();
    
    int currentBufferLength = std::min(BLOCKSIZE, bufferNumSamples - startIndex);
    
        // Go through all events in the track
    while (startIndex < bufferNumSamples && midiEventIndex < numMidiEventsInTrack) {
        double startTime = (double)startIndex / SAMPLE_RATE;
        double endTime = startTime + (double)currentBufferLength / SAMPLE_RATE;
        midiBuffer.clear();
        MidiMessage message = track.getEventPointer(midiEventIndex)->message;
        double messageTimeStamp = message.getTimeStamp();
        
            // Go through all events within each buffer
        while (messageTimeStamp < endTime && midiEventIndex < numMidiEventsInTrack) {
            int messageIndex = roundToIntAccurate(messageTimeStamp * SAMPLE_RATE);
            DEBUG_LOG("\t\t\tAdding Midi event %s\n", message.getDescription().toRawUTF8());
            midiBuffer.addEvent(message, messageIndex); // KRK_FIXME not JUST startIndex, right? Need to interpolate within the buffer time frame
            if (message.isNoteOn()) {
                DEBUG_LOG("Note On | Start Index: %d | Buffer Len: %d\n", messageIndex, currentBufferLength);
//                mSynth.noteOn(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity());
            }
            else if (message.isNoteOff()) {
                DEBUG_LOG("Note Off | Start Index: %d | Buffer Len: %d\n", messageIndex, currentBufferLength);
//                mSynth.noteOff(message.getChannel(), message.getNoteNumber(), message.getFloatVelocity(), true);
            }
            
            if (++midiEventIndex < numMidiEventsInTrack) {
                message = track.getEventPointer(midiEventIndex)->message;
                messageTimeStamp = message.getTimeStamp();
            }
            
        }
        
        mSynth.renderNextBlock(mBuffer, midiBuffer, startIndex, currentBufferLength);
        
        startIndex += BLOCKSIZE;
        currentBufferLength = std::min(bufferNumSamples - startIndex - 1, BLOCKSIZE);
    }
}
