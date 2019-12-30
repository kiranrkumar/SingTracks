/*
  ==============================================================================

    VocalGroupBus.cpp
    Created: 29 Dec 2019 5:59:05pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "VocalGroupBus.h"

VocalGroupBus::VocalGroupBus(String displayName, float gainValue, float panValue) : mDisplayName(displayName), mGainValue(gainValue), mPanValue(panValue) {}

VocalGroupBus::VocalGroupBus(const VocalGroupBus &busToCopy) : mBus(busToCopy.getBus()), mDisplayName(busToCopy.getDisplayName()), mGainValue(busToCopy.getGainValue()), mPanValue(busToCopy.getPanValue()) {}

VocalBus VocalGroupBus::getBus() const
{
    return mBus;
}

void VocalGroupBus::setDisplayName(String displayName)
{
    mDisplayName = displayName;
}

String VocalGroupBus::getDisplayName() const
{
    return mDisplayName;
}

void VocalGroupBus::setGainValueFromDb(float dbValue)
{
    mGainValue = std::pow(10.f, dbValue/20.f);
}

float VocalGroupBus::getGainValue() const
{
    return mGainValue;
}

void VocalGroupBus::setPanValue(float pan, float minPan, float maxPan)
{
    mPanValue = (pan - minPan) / (maxPan - minPan);
}

float VocalGroupBus::getPanValue() const
{
    return mPanValue;
}
