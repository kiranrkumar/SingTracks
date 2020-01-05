/*
  ==============================================================================

    VocalBusSettings.h
    Created: 29 Dec 2019 9:06:05am
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "AudioDefines.h"

typedef std::vector<float> ChannelGainsArray;

class VocalBusSettings {
public:
    VocalBusSettings(const String &displayName = "", float gainValue = 0, float panValue = 0);
    VocalBusSettings(const VocalBusSettings&);
    
    void setBus(VocalBus);
    VocalBus getBus() const;
    
    void setDisplayName(String displayName);
    String getDisplayName() const;
    
    void setGainValueFromDb(float dbValue);
    float getGainValue() const;
    static ChannelGainsArray getChannelGains(VocalBusSettings *busSettings);
    
    void setPanValue(float pan, float minPan = -64, float maxPan = 63);
    float getPanValue() const;
    
private:
    VocalBus mBus;
    String mDisplayName;
    float mGainValue;
    float mPanValue;
};
