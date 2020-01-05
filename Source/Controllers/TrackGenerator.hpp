//
//  TrackGenerator.hpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/28/19.
//

#ifndef TrackGenerator_hpp
#define TrackGenerator_hpp

#include <stdio.h>
#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Model/AudioDefines.h"

class VocalTrack;
class VocalBusSettings;

class TrackGenerator {
private:
    constexpr static const double DEFAULT_SAMPLE_RATE = 48000;
    
#pragma mark - Public
public:
    TrackGenerator(double sampleRate = DEFAULT_SAMPLE_RATE);
    ~TrackGenerator();
    
    bool readMidiDataFromFile(File&);
    const MidiFile& getMidiFile() const;
    double getSampleRate() const;
    int getNumTracks() const;
    bool isMusicalTrack(int trackNum);
    
    void printSummary();
    
    void renderAudio(BusToSettingsMap&, BusToBuffersMap&);

#pragma mark - Private
private:
    // MIDI
    double getTrueLastTimestamp(MidiFile&);
    void renderMidiTrack(const MidiMessageSequence &track, AudioBuffer<float> &outputBuffer);
    void renderAllMidiTracks(AudioBuffer<float> &outputBuffer);
    
    // Audio
    void prepareOutputBuffer(AudioBuffer<float> &outputBuffer);
    void renderAudioBuffer(AudioBuffer<float> &ioBuffer, BusToSettingsMap &busToSettingsMap, BusToBuffersMap &busToBuffersMap, VocalBus bus);
    bool writeAudioToFile(AudioBuffer<float>&, String);
    void writeAudioBuffersToFile(std::vector<AudioBuffer<float>> &buffers);
    
    static void renderContentsOfBusToBuffer(AudioBuffer<float> &ioBuffer, VocalBusSettings *busSettings, std::vector<AudioBuffer<float>> &busBuffers);
    static std::vector<AudioBuffer<float>> renderPrimaryBusToBuffers(const AudioBuffer<float> &originalOutputBuffer, BusToSettingsMap &busToSettingsMap, BusToBuffersMap &busToBuffersMap);
    
    MidiFile mMidiFile;
    double mSampleRate;
    Synthesiser mSynth;
};

#endif /* TrackGenerator_hpp */
