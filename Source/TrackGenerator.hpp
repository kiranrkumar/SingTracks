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
    void setMidiFile(MidiFile*);
    MidiFile* getMidiFile() const;
    
    void printSummary();
    void renderMidiToAudio();
private:
    double getTrueLastTimestamp(MidiFile*);
    void normalizeBuffer(AudioBuffer<float>&, float);
    bool writeAudioToFile(AudioBuffer<float>&);
    MidiFile* mMidiFile;
    float mSampleRate;
    Synthesiser mSynth;
};

#endif /* TrackGenerator_hpp */
