/*
  ==============================================================================

    MIDITrackSynthesizer.h
    Created: 26 Nov 2019 9:37:46am
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MIDITrackSynthesizerSound : public SynthesiserSound {
public:
    bool appliesToNote (int midiNoteNumber) override;
    bool appliesToChannel (int midiChannel) override;
private:
    
};

class MIDITrackSynthesizerVoice : public SynthesiserVoice {
public:
    bool canPlaySound (SynthesiserSound*) override;
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
private:
    double getNextSineSample();
    double mFrequency;
    double mGain;
    bool mIsTailing;
};
