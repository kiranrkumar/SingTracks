/*
  ==============================================================================

    TrackSettingsComponent.h
    Created: 26 Dec 2019 10:04:41am
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class TrackSettingsComponent : public Component, private Button::Listener, private Slider::Listener {
public:
    TrackSettingsComponent();
    ~TrackSettingsComponent();
    
    void paint(Graphics &g) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override;
    void buttonClicked (Button* button) override;

private:
    Slider mGainSlider;
    Slider mPanSlider;
};
