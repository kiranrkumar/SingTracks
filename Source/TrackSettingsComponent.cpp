/*
  ==============================================================================

    TrackSettingsComponent.cpp
    Created: 26 Dec 2019 10:04:41am
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TrackSettingsComponent.h"

TrackSettingsComponent::TrackSettingsComponent()
{
    mGainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 45, 25);
    mGainSlider.setNumDecimalPlacesToDisplay(1);
    mGainSlider.setRange(Range<double>(-80.0, 6.0), 1.0);
    mGainSlider.setValue(0.0);
    mGainSlider.setTextValueSuffix("dB");
    mGainSlider.addListener(this);
    addAndMakeVisible(mGainSlider);
    
    mPanSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mPanSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 45, 25);
    mPanSlider.setNumDecimalPlacesToDisplay(0);
    mPanSlider.setRange(Range<double>(-64, 63), 1);
    mPanSlider.setValue(0);
    mPanSlider.addListener(this);
    addAndMakeVisible(mPanSlider);
}

TrackSettingsComponent::~TrackSettingsComponent() {}

void TrackSettingsComponent::paint(Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void TrackSettingsComponent::resized()
{
    Rectangle<int> area = getLocalBounds();
    int areaHeight = area.getHeight();
    int areaWidth = area.getWidth();
    
    const int gainWidth = 85;
    const int panWidth = 95;
    const int gainVerticalPadding = 10;
    const int spaceBetweenControls = 15;
    
    int spaceAtSides = areaWidth - gainWidth - panWidth - spaceBetweenControls;
    
    mGainSlider.setBounds(spaceAtSides/2 + spaceBetweenControls/2, gainVerticalPadding, gainWidth, areaHeight - gainVerticalPadding * 2);
    mPanSlider.setBounds(areaWidth - spaceAtSides/2 - panWidth - spaceBetweenControls/2, areaHeight - panWidth - gainVerticalPadding, panWidth, panWidth);
}

#pragma mark - Listener Overrides
void TrackSettingsComponent::sliderValueChanged(Slider* slider)
{
    
}
void TrackSettingsComponent::buttonClicked(Button* button)
{

}
