/*
  ==============================================================================

    TrackSettingsComponent.h
    Created: 26 Dec 2019 10:04:41am
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Model/VocalBusSettings.h"

class TrackSettingsComponent : public Component {
public:
    TrackSettingsComponent(String name);
    ~TrackSettingsComponent();
    
    void paint(Graphics &g) override;
    void resized() override;
    
    VocalBusSettings getBusSettings() const;

private:
    Slider mDbSlider;
    Slider mPanSlider;
    VocalBusSettings mBusSettings;
};
