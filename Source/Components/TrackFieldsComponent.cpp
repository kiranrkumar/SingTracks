/*
  ==============================================================================

    TrackFieldsComponent.cpp
    Created: 21 Dec 2019 10:10:48pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TrackFieldsComponent.h"

#include "../Model/VocalTrack.h"

const int cLeftInset = 30;
const int cRightInset = 30;
const int cSoloButtonWidth = 80;
const int cSoloButtonNameFieldPadding = 20;

TrackFieldsComponent::TrackFieldsComponent(VocalTrack &track)
{
    mIsSoloButton.setClickingTogglesState(true);
    mIsSoloButton.addListener(this);
    mIsSoloButton.setButtonText("Is Solo");
    
    mNameField.setMultiLine(false);
    mNameField.applyFontToAllText(Font(16));
    mNameField.setText(track.getDisplayName());
    
    addAndMakeVisible(mIsSoloButton);
    addAndMakeVisible(mNameField);
}

TrackFieldsComponent::~TrackFieldsComponent()
{
}

void TrackFieldsComponent::paint(Graphics &g)
{
}

void TrackFieldsComponent::resized()
{
    int width = getWidth();
    int height = getHeight();
    
    mNameField.setBounds(cLeftInset, 0, width - cLeftInset - cRightInset - cSoloButtonWidth - cSoloButtonNameFieldPadding, height);
    mIsSoloButton.setBounds(width - cSoloButtonWidth - cRightInset, 0, cSoloButtonWidth, height);
}

#pragma mark - Button Listener
void TrackFieldsComponent::buttonClicked(Button *button)
{
}
