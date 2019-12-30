/*
  ==============================================================================

    VocalGroupBus.h
    Created: 29 Dec 2019 9:06:05am
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class VocalGroupBus {
public:
    VocalGroupBus(String displayName = "", float gainValue = 0, float panValue = 0);
    
    void setDisplayName(String displayName);
    String getDisplayName();
    
    void setGainValue(float gain);
    float getGainValue();
    
    void setPanValue(float pan);
    float getPanValue();
    
private:
    String mDisplayName;
    float mGainValue;
    float mPanValue;
};
