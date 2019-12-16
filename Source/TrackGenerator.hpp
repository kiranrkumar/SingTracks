//
//  TrackGenerator.hpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/28/19.
//

#ifndef TrackGenerator_hpp
#define TrackGenerator_hpp

#include <stdio.h>

#include "../JuceLibraryCode/JuceHeader.h"

class TrackGenerator {
public:
    TrackGenerator();
    ~TrackGenerator();
    bool getMidiDataFromFile(File&);
    void setMidiFile(MidiFile&);
    const MidiFile& getMidiFile() const;
    
    void printSummary();
    void renderAudio();
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
