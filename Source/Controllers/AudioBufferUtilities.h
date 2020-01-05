/*
  ==============================================================================

    AudioBufferUtilities.h
    Created: 4 Jan 2020 5:42:48pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../Model/VocalBusSettings.h"

void applyChannelGainsToBuffer(const ChannelGainsArray &channelGains, AudioBuffer<float> &ioBuffer);
AudioBuffer<float> splitMonoBufferWithChannelGains(const AudioBuffer<float> &inBuffer, const ChannelGainsArray &channelGains, bool flipPhase = false);
void addToBuffer(AudioBuffer<float> &outBuffer, const AudioBuffer<float> &bufferToAdd);
