/*
  ==============================================================================

    VocalGroupBus.cpp
    Created: 29 Dec 2019 5:59:05pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "VocalGroupBus.h"

VocalGroupBus::VocalGroupBus(String displayName, float gainValue, float panValue) : mDisplayName(displayName), mGainValue(gainValue), mPanValue(panValue)
{
}

void VocalGroupBus::setDisplayName(String displayName)
{
    mDisplayName = displayName;
}

String VocalGroupBus::getDisplayName()
{
    return mDisplayName;
}

void VocalGroupBus::setGainValue(float gain)
{
    mGainValue = gain;
}

float VocalGroupBus::getGainValue()
{
    return mGainValue;
}

void VocalGroupBus::setPanValue(float pan, float minPan, float maxPan)
{
    mPanValue = (pan - minPan) / (maxPan - minPan);
}

float VocalGroupBus::getPanValue()
{
    return mPanValue;
}
