//
//  TrackGenerator.cpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/28/19.
//

#include "TrackGenerator.hpp"

#include "AudioBufferUtilities.h"
#include "MIDITrackSynthesizer.h"
#include "../Model/VocalTrack.h"
#include "../Model/VocalBusSettings.h"

const int NUM_OUTPUT_CHANNELS = 2;
const int NUM_SYNTH_VOICES = 10;

TrackGenerator::TrackGenerator(double sampleRate) {
    mSampleRate = sampleRate;
    
    mSynth.clearVoices();
    for (int i = 0; i < NUM_SYNTH_VOICES; ++i) {
        mSynth.addVoice(new MIDITrackSynthesizerVoice());
    }
    
    mSynth.clearSounds();
    mSynth.addSound(new MIDITrackSynthesizerSound());
    mSynth.setCurrentPlaybackSampleRate(mSampleRate);
}

TrackGenerator::~TrackGenerator() {
    mSynth.clearVoices();
    mSynth.clearSounds();
    mMidiFile.clear();
}

bool TrackGenerator::readMidiDataFromFile(File& file) {
    FileInputStream inStream(file);
    return mMidiFile.readFrom(inStream);
}

const MidiFile& TrackGenerator::getMidiFile() const {
    return mMidiFile;
}

double TrackGenerator::getSampleRate() const {
    return mSampleRate;
}

int TrackGenerator::getNumTracks() const {
    return mMidiFile.getNumTracks();
}

void TrackGenerator::printSummary() {
    mMidiFile.convertTimestampTicksToSeconds();
    DEBUG_LOG("Num tracks: %d\n", mMidiFile.getNumTracks());
    DEBUG_LOG("Time format: %d\n", mMidiFile.getTimeFormat());
}

    static void renderContentsOfBusToBuffer(AudioBuffer<float> &ioBuffer, VocalBusSettings *busSettings, std::vector<AudioBuffer<float>> &busBuffers) {
        
        ChannelGainsArray channelGains = VocalBusSettings::getChannelGains(busSettings);
        for (auto buffer : busBuffers) {
            AudioBuffer<float> bufferCopyWithGains = splitMonoBufferWithChannelGains(buffer, channelGains);
            addToBuffer(ioBuffer, bufferCopyWithGains);
        }
    }

void TrackGenerator::renderAudioBuffer(AudioBuffer<float> &ioBuffer, BusToSettingsMap &busToSettingsMap, BusToBuffersMap &busToBuffersMap, VocalBus bus) {
    jassert(ioBuffer.getNumChannels() == 2);
    
    VocalBusSettings *busSettings = busToSettingsMap[bus].get();
    std::vector<AudioBuffer<float>> busBuffers = busToBuffersMap[bus];
    
    if (bus == Solo || bus == Background) {
        renderContentsOfBusToBuffer(ioBuffer, busSettings, busBuffers);
    }
    else if (bus == Primary) {
        VocalBusSettings *bgSettings = busToSettingsMap[Background].get();
        ChannelGainsArray bgChannelGains = VocalBusSettings::getChannelGains(bgSettings);
        ChannelGainsArray primChannelGains = VocalBusSettings::getChannelGains(busSettings);
        
        // For each background buffer, reverse the bg gain, apply primary gain, and write to file
        int fileIndex = 0;
        std::vector<AudioBuffer<float>> bgBuffers = busToBuffersMap[Background];
        for (auto buffer : bgBuffers) {
            AudioBuffer<float> outputCopy(ioBuffer);
            
            AudioBuffer<float> bgBuffersPhaseFlipped = splitMonoBufferWithChannelGains(buffer, bgChannelGains, true);
            addToBuffer(outputCopy, bgBuffersPhaseFlipped);
            
            AudioBuffer<float> primaryBuffers = splitMonoBufferWithChannelGains(buffer, primChannelGains);
            addToBuffer(outputCopy, primaryBuffers);
            
            String fileName = "~/audioRender_" + std::to_string(fileIndex++) + ".wav";
            DEBUG_LOG("Writing file\n");
            writeAudioToFile(outputCopy, fileName);
        }
    }
}

void TrackGenerator::renderAudio(BusToSettingsMap &busToSettingsMap, BusToBuffersMap &busToBuffersMap)
{
    // Initialize an empty output buffer
    int numSamples = static_cast<int>(ceilf(DEFAULT_SAMPLE_RATE * getTrueLastTimestamp(mMidiFile)));
    AudioBuffer<float> outputBuffer(NUM_OUTPUT_CHANNELS, numSamples);
    outputBuffer.clear();

    renderAudioBuffer(outputBuffer, busToSettingsMap, busToBuffersMap, Solo);
    renderAudioBuffer(outputBuffer, busToSettingsMap, busToBuffersMap, Background);
    
    // WARNING - this writes to file as well. FIX THIS!
    renderAudioBuffer(outputBuffer, busToSettingsMap, busToBuffersMap, Primary);
}

bool TrackGenerator::isMusicalTrack(int trackNum)
{
    if (trackNum < 0 || trackNum >= mMidiFile.getNumTracks()) {
        return false;
    }
    
    const MidiMessageSequence *sequence = mMidiFile.getTrack(trackNum);
    
    for (int eventIndex = sequence->getNumEvents() - 1; eventIndex >= 0; --eventIndex) {
        if (sequence->getEventPointer(eventIndex)->message.isNoteOff()) {
            return true;
        }
    }
    
    return false;
}

void TrackGenerator::prepareOutputBuffer(AudioBuffer<float> &outputBuffer) {
    int numTracks = mMidiFile.getNumTracks();
    DEBUG_LOG("%d tracks\n", numTracks);
    double lastTimeStamp = getTrueLastTimestamp(mMidiFile);
    int numSamples = int(ceil(lastTimeStamp * mSampleRate));
    
    outputBuffer.setSize(NUM_OUTPUT_CHANNELS, numSamples);
    outputBuffer.clear();
}

void TrackGenerator::renderAllMidiTracks(AudioBuffer<float> &outputBuffer) {
    for (int i = 0; i < mMidiFile.getNumTracks(); ++i) {
       const MidiMessageSequence *track = mMidiFile.getTrack(i);
       int numMidiEventsInTrack = track->getNumEvents();
       DEBUG_LOG("\t%d: %d events\n", i, numMidiEventsInTrack);
       
       renderMidiTrack(*track, outputBuffer);
   }
}

void TrackGenerator::renderMidiTrack(const MidiMessageSequence &track, AudioBuffer<float> &outputBuffer) {
    const int BLOCKSIZE = 256;
    MidiBuffer midiBuffer;
    int startIndex = 0;
    int midiEventIndex = 0;
    
    int bufferNumSamples = outputBuffer.getNumSamples();
    int numMidiEventsInTrack = track.getNumEvents();
    DEBUG_LOG("\t%d events\n", numMidiEventsInTrack);
    
    int currentBufferLength = std::min(BLOCKSIZE, bufferNumSamples - startIndex);
    
        // Go through all events in the track
    while (startIndex < bufferNumSamples && midiEventIndex < numMidiEventsInTrack) {
        double startTime = (double)startIndex / mSampleRate;
        double endTime = startTime + (double)currentBufferLength / mSampleRate;
        midiBuffer.clear();
        MidiMessage message = track.getEventPointer(midiEventIndex)->message;
        double messageTimeStamp = message.getTimeStamp();
        
            // Go through all events within each buffer
        while (messageTimeStamp < endTime && midiEventIndex < numMidiEventsInTrack) {
            int messageIndex = roundToIntAccurate(messageTimeStamp * mSampleRate);
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
        
        mSynth.renderNextBlock(outputBuffer, midiBuffer, startIndex, currentBufferLength);
        
        startIndex += BLOCKSIZE;
        currentBufferLength = std::min(bufferNumSamples - startIndex - 1, BLOCKSIZE);
    }
}

void TrackGenerator::normalizeBuffer(AudioBuffer<float>& buffer, float maxMagnitude)
{
    int numSamples = buffer.getNumSamples();
    float trueMaxMag = std::min(maxMagnitude, 1.f);
    buffer.applyGain(0, numSamples, trueMaxMag / buffer.getMagnitude(0, numSamples));
}

bool TrackGenerator::writeAudioToFile(AudioBuffer<float>& buffer, String fileName)
{
    DEBUG_LOG("Writing audio to file...\n");
    File outFile(fileName);
    
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

    // KRK_FIXME there has to be a better way to do this, but for some MIDIs created in Logic
    //  (particularly ones that are more than one track), there's an extra first track that
    //  contains all of the initial "global" metadata (time signature, key signature, etc) plus a
    //  track-end event with a LARGE timestamp that's causing the program to render
    //  way too many samples.
    //
    // This (hopefully) temporary "fix" searches all tracks for the last "note off" event
    //  and grabs the timestamp from that.
double TrackGenerator::getTrueLastTimestamp(MidiFile& midiFile)
{
    double lastTimeStamp = 0;
    int numTracks = midiFile.getNumTracks();
    
    for (int trackIndex = 0; trackIndex < numTracks; ++trackIndex) {
        const MidiMessageSequence *track = mMidiFile.getTrack(trackIndex);
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
