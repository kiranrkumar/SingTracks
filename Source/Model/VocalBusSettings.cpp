/*
  ==============================================================================

    VocalBusSettings.cpp
    Created: 29 Dec 2019 5:59:05pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "VocalBusSettings.h"

static void printDescription(VocalBusSettings &settings) {
    std::cout << "VocalBusSettings - " << &settings << std::endl;
    std::cout << "\t" << settings.getDisplayName() << std::endl;
    std::cout << "\t" << settings.getGainValue() << std::endl;
    std::cout << "\t" << settings.getPanValue() << std::endl;
}

VocalBusSettings::VocalBusSettings(const String &displayName, float gainValue, float panValue) : mDisplayName(displayName), mGainValue(gainValue), mPanValue(panValue)
{
    printDescription(*this);
}

VocalBusSettings::VocalBusSettings(const VocalBusSettings &settingsToCopy) : mBus(settingsToCopy.getBus()), mDisplayName(settingsToCopy.getDisplayName()), mGainValue(settingsToCopy.getGainValue()), mPanValue(settingsToCopy.getPanValue())
{
    printDescription(*this);
}

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
    std::cout << "Gain: " << mGainValue;
    mGainValue = std::pow(10.f, dbValue/20.f);
    std::cout << " to " << mGainValue << std::endl;
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
