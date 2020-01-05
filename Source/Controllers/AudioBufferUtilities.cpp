/*
  ==============================================================================

    AudioBufferUtilities.cpp
    Created: 4 Jan 2020 5:42:48pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "AudioBufferUtilities.h"

void applyChannelGainsToBuffer(const ChannelGainsArray &channelGains, AudioBuffer<float> &ioBuffer) {
    jassert(ioBuffer.getNumChannels() == channelGains.size());
    
    int numSamples = ioBuffer.getNumSamples();
    for (int i = 0; i < channelGains.size(); ++i) {
        ioBuffer.applyGain(i, 0, numSamples, channelGains[i]);
    }
}

AudioBuffer<float> splitMonoBufferWithChannelGains(const AudioBuffer<float> &inBuffer, const ChannelGainsArray &channelGains, bool flipPhase) {
    
    jassert(inBuffer.getNumChannels() == 1);
    int numSamples = inBuffer.getNumSamples();
    int numOutChannels = static_cast<int>(channelGains.size());
    int phase = flipPhase ? -1 : 1;
    
    AudioBuffer<float> outBuffer(numOutChannels, numSamples);
    for (int i = 0; i < numOutChannels; ++i) {
        outBuffer.copyFrom(i, 0, inBuffer, 0, 0, numSamples);
        outBuffer.applyGain(i, 0, numSamples, channelGains[i] * phase);
    }
    
    return outBuffer;
}

void addToBuffer(AudioBuffer<float> &outBuffer, const AudioBuffer<float> &bufferToAdd) {
    int numChannels = numChannels = outBuffer.getNumChannels();
    jassert(numChannels == bufferToAdd.getNumChannels());
    
    int numSamples = std::min(outBuffer.getNumSamples(), bufferToAdd.getNumSamples());
    
    for (int ch = 0; ch < numChannels; ++ch) {
        outBuffer.addFrom(ch, 0, bufferToAdd, ch, 0, numSamples);
    }
}
