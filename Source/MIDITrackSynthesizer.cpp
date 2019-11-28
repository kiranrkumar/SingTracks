/*
  ==============================================================================

    MIDITrackSynthesizer.cpp
    Created: 26 Nov 2019 9:37:46am
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "MIDITrackSynthesizer.h"

#include <cmath>

#pragma mark - Synthesizer Sound
bool MIDITrackSynthesizerSound::appliesToNote(int midiNoteNumber)
{
    return true;
}

bool MIDITrackSynthesizerSound::appliesToChannel(int midiChannel)
{
    // KRK_FIXME - should I limit this?
    return true;
}

#pragma mark - Synthesizer Voice
bool MIDITrackSynthesizerVoice::canPlaySound(SynthesiserSound *synthSound)
{
    return dynamic_cast<MIDITrackSynthesizerSound*>(synthSound) != nullptr;
}

void MIDITrackSynthesizerVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    mSineAlpha = 0;
    mIsTailing = false;
    mFrequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    mGain = velocity / 127.0;
    DEBUG_LOG("start note: %d | %2.f Hz\n", midiNoteNumber, mFrequency);
}

void MIDITrackSynthesizerVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff) {
        mIsTailing = true;
    }
    else {
        mGain = 0;
        clearCurrentNote();
    }
    DEBUG_LOG("start note: %d | %2.f Hz\n", midiNoteNumber, mFrequency);
}

// Not concerned with pitch wheel and controller functions
void MIDITrackSynthesizerVoice::pitchWheelMoved (int newPitchWheelValue) {}
void MIDITrackSynthesizerVoice::controllerMoved (int controllerNumber, int newControllerValue) {}

void MIDITrackSynthesizerVoice::renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    for (int n = startSample; n < startSample + numSamples; ++n) {
        float sample = getNextSineSample();
        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
            mGain = getNextTailValue(mGain);
            outputBuffer.addSample(c, n, sample * mGain);
        }
    }
}

float MIDITrackSynthesizerVoice::getNextSineSample()
{
    const float twoPi = 2 * M_PI;
    mSineAlpha += (twoPi * mFrequency / getSampleRate());
    if (mSineAlpha > twoPi) {
        mSineAlpha -= twoPi;
    }
    
    float sample = std::sin(mSineAlpha);
    return sample;
}

float MIDITrackSynthesizerVoice::getNextTailValue(float gain)
{
    if (mIsTailing && gain <= 0.00005) {
        gain = 0;
        mIsTailing = false;
        clearCurrentNote();
    }
    else if (mIsTailing) {
        gain *= 0.99;
    }
    
    return gain;
}
