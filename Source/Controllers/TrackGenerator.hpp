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

class VocalTrack;
class VocalBusSettings;

class TrackGenerator {
private:
    constexpr static const double DEFAULT_SAMPLE_RATE = 48000;
    
public:
    TrackGenerator(double sampleRate = DEFAULT_SAMPLE_RATE);
    ~TrackGenerator();
    
    bool readMidiDataFromFile(File&);
    const MidiFile& getMidiFile() const;
    double getSampleRate() const;
    int getNumTracks() const;
    
    void printSummary();
    bool isMusicalTrack(int trackNum);
    void renderAudio();
    void renderAudio(OwnedArray<VocalBusSettings>& busSettings, OwnedArray<VocalTrack>& tracks);
private:
    void prepareOutputBuffer(AudioBuffer<float> &outputBuffer);
    void renderAllMidiTracks(AudioBuffer<float> &outputBuffer);
    void renderMidiTrack(const MidiMessageSequence &track, AudioBuffer<float> &outputBuffer);
    void normalizeBuffer(AudioBuffer<float>&, float);
    bool writeAudioToFile(AudioBuffer<float>&);
    
    double getTrueLastTimestamp(MidiFile&);
    
    MidiFile mMidiFile;
    double mSampleRate;
    Synthesiser mSynth;
};

#endif /* TrackGenerator_hpp */
