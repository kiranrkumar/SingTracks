/*
  ==============================================================================

    VocalBusSettings.cpp
    Created: 29 Dec 2019 5:59:05pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "VocalBusSettings.h"

VocalBusSettings::VocalBusSettings(const String &displayName, float gainValue, float panValue) : mDisplayName(displayName), mGainValue(gainValue), mPanValue(panValue)
{

}

VocalBusSettings::VocalBusSettings(const VocalBusSettings &settingsToCopy) : mBus(settingsToCopy.getBus()), mDisplayName(settingsToCopy.getDisplayName()), mGainValue(settingsToCopy.getGainValue()), mPanValue(settingsToCopy.getPanValue()) {}

void VocalBusSettings::setBus(VocalBus bus)
{
    mBus = bus;
}

VocalBus VocalBusSettings::getBus() const
{
    return mBus;
}

void VocalBusSettings::setDisplayName(String displayName)
{
    mDisplayName = displayName;
}

String VocalBusSettings::getDisplayName() const
{
    return mDisplayName;
}

void VocalBusSettings::setGainValueFromDb(float dbValue)
{
    mGainValue = std::pow(10.f, dbValue/20.f);
}

float VocalBusSettings::getGainValue() const
{
    return mGainValue;
}

void VocalBusSettings::setPanValue(float pan, float minPan, float maxPan)
{
    mPanValue = (pan - minPan) / (maxPan - minPan);
}

float VocalBusSettings::getPanValue() const
{
    return mPanValue;
}
