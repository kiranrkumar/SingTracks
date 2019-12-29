/*
  ==============================================================================

    TrackSettingsComponent.cpp
    Created: 26 Dec 2019 10:04:41am
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TrackSettingsComponent.h"

TrackSettingsComponent::TrackSettingsComponent(String name) : mDisplayName(name)
{
    const int textBoxWidth = 50;
    const int textBoxHeight = 25;
    
    mGainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mGainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    mGainSlider.setNumDecimalPlacesToDisplay(1);
    mGainSlider.setRange(Range<double>(-80.0, 6.0), 1.0);
    mGainSlider.setValue(0.0);
    mGainSlider.setTextValueSuffix(" dB");
    mGainSlider.addListener(this);
    addAndMakeVisible(mGainSlider);
    
    mPanSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mPanSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
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
    
    g.setColour(Colours::white);
    g.setFont (Font (16.0f));
    g.drawText(mDisplayName, getLocalBounds(), Justification::centredTop);
}

void TrackSettingsComponent::resized()
{
    Rectangle<int> area = getLocalBounds();
    int areaHeight = area.getHeight();
    int areaWidth = area.getWidth();
    
    const int gainWidth = 65;
    const int panWidth = 95;
    const int panHeight = 95;
    const int gainVerticalPadding = 15;
    const int horizontalOffsetFromCenter = 2;
    
    mGainSlider.setBounds(areaWidth/2 - gainWidth - horizontalOffsetFromCenter, gainVerticalPadding, gainWidth, areaHeight - gainVerticalPadding * 2);
    mPanSlider.setBounds(areaWidth/2 + horizontalOffsetFromCenter, areaHeight - panWidth - gainVerticalPadding, panWidth, panHeight);
}

#pragma mark - Listener Overrides
void TrackSettingsComponent::sliderValueChanged(Slider* slider)
{
    
}
void TrackSettingsComponent::buttonClicked(Button* button)
{

}
