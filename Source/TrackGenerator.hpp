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

#define RUN_UNIT_TESTS 0

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

class MIDIReadTest : public UnitTest
{
public:
    MIDIReadTest() : UnitTest ("Read a valid MIDI file") {}
    
    void runTest() override;
    
    void setUp();
    bool readMIDIFile();
    bool getNumTracks();
    
private:
    TrackGenerator mTrackGenerator;
};

class FileWriteTest : public UnitTest
{
public:
    FileWriteTest() : UnitTest ("Write an audio file to disk") {}
    
    void runTest() override;
    
    void setUp();
    bool createFileObject(String);
    bool writeFileToDisk();
    
private:
    File mFileObject;
    TimeSliceThread mBackgroundThread { "Audio Recorder (Writer) Thread" }; // the thread that will write our audio data to disk
    std::unique_ptr<AudioFormatWriter::ThreadedWriter> mThreadedWriter; // the FIFO used to buffer the incoming data
    float mSampleRate = 48000;
    int64 mNextSampleNum = 0;
    
    CriticalSection mWriterLock;
    std::atomic<AudioFormatWriter::ThreadedWriter*> activeWriter { nullptr };
};

#endif /* TrackGenerator_hpp */
