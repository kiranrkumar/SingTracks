/*
  ==============================================================================

    TrackSettingsComponent.cpp
    Created: 26 Dec 2019 10:04:41am
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TrackSettingsComponent.h"

TrackSettingsComponent::TrackSettingsComponent(String name)
{
    const int textBoxWidth = 50;
    const int textBoxHeight = 25;
    
    mBus.setDisplayName(name);
    mBus.setPanValue(0.f);
    mBus.setGainValueFromDb(0.f);
    
    mDbSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mDbSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    mDbSlider.setNumDecimalPlacesToDisplay(1);
    mDbSlider.setRange(Range<double>(-80.0, 6.0), 1.0);
    mDbSlider.setValue(0.0);
    mDbSlider.setTextValueSuffix(" dB");
    mDbSlider.onValueChange = [this] {
        mBus.setGainValueFromDb(mDbSlider.getValue());
    };
    addAndMakeVisible(mDbSlider);
    
    mPanSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    mPanSlider.setTextBoxStyle(Slider::TextBoxBelow, false, textBoxWidth, textBoxHeight);
    mPanSlider.setNumDecimalPlacesToDisplay(0);
    mPanSlider.setRange(Range<double>(-64, 63), 1);
    mPanSlider.setValue(0);
    mPanSlider.onValueChange = [this] {
        mBus.setPanValue(mPanSlider.getValue());
    };
    addAndMakeVisible(mPanSlider);
}

TrackSettingsComponent::~TrackSettingsComponent() {}

#pragma mark Component
void TrackSettingsComponent::paint(Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    
    g.setColour(Colours::white);
    g.setFont (Font (16.0f));
    g.drawText(mBus.getDisplayName(), getLocalBounds(), Justification::centredTop);
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
    
    mDbSlider.setBounds(areaWidth/2 - gainWidth - horizontalOffsetFromCenter, gainVerticalPadding, gainWidth, areaHeight - gainVerticalPadding * 2);
    mPanSlider.setBounds(areaWidth/2 + horizontalOffsetFromCenter, areaHeight - panWidth - gainVerticalPadding, panWidth, panHeight);
}

#pragma mark Accessors
VocalGroupBus TrackSettingsComponent::getBus() const
{
    return mBus;
}
