/*
  ==============================================================================

    MidiFile_TEST.h
    Created: 3 Dec 2019 8:45:00pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "TrackGenerator.hpp"

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
