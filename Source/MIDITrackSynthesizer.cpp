/*
  ==============================================================================

    MIDITrackSynthesizer.cpp
    Created: 26 Nov 2019 9:37:46am
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "MIDITrackSynthesizer.h"

#include <cmath>

#pragma mark - MIDITrackSynthesizerSound
bool MIDITrackSynthesizerSound::appliesToNote(int midiNoteNumber)
{
    return true;
}

bool MIDITrackSynthesizerSound::appliesToChannel(int midiChannel)
{
    // KRK_FIXME - should I limit this?
    return true;
}

#pragma mark - MIDITrackSynthesizerVoice
bool MIDITrackSynthesizerVoice::canPlaySound(SynthesiserSound *synthSound)
{
    return dynamic_cast<MIDITrackSynthesizerSound*>(synthSound) != nullptr;
}

void MIDITrackSynthesizerVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition)
{
    mIsTailing = false;
    mFrequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    mGain = velocity / 127.0;
    std::cout << "start note: " << midiNoteNumber << " | " << mFrequency << " Hz" << std::endl;
}

void MIDITrackSynthesizerVoice::stopNote (float velocity, bool allowTailOff)
{
    mIsTailing = true;
    std::cout << "stop note: " << mFrequency << " Hz" << std::endl;
    mGain = 0;
    clearCurrentNote();
}

void MIDITrackSynthesizerVoice::pitchWheelMoved (int newPitchWheelValue)
{
    // KRK_FIXME - to do
}

void MIDITrackSynthesizerVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    // KRK_FIXME - to do
}
void MIDITrackSynthesizerVoice::renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    for (int n = 0; n < numSamples; ++n) {
        double sample = getNextSineSample();
        for (int c = 0; c < outputBuffer.getNumChannels(); ++c) {
            if (mIsTailing) {
                mGain *= 0.65;
            }
            if (mGain <= 0.005) {
                mGain = 0;
                mIsTailing = false;
            }
            outputBuffer.addSample(c, n, sample * mGain);
        }
    }
}

double MIDITrackSynthesizerVoice::getNextSineSample()
{
    static int sampleNum = 0;
    static double alpha = 0;
    const double twoPi = 2 * M_PI;
    alpha += (twoPi * mFrequency / getSampleRate());
    if (alpha > twoPi) {
        alpha -= twoPi;
    }
    
    double sample = std::sin(alpha);
//    printf("%d | Alpha: %.2f | Sample: %.2f\n", sampleNum++, alpha, sample);
    return sample;
}
