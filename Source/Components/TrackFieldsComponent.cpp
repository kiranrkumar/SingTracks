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
const int cIsSoloButtonWidth = 140;
const int cSoloButtonNameFieldPadding = 20;

TrackFieldsComponent::TrackFieldsComponent(VocalTrack *track)
{
    mVocalTrack.reset(track);
    
    mIsSoloButton.setClickingTogglesState(true);
    mIsSoloButton.addListener(this);
    mIsSoloButton.setButtonText("Is Solo/Harmony");
    
    mNameField.setMultiLine(false);
    mNameField.applyFontToAllText(Font(16));
    mNameField.setText(track->getDisplayName());
    
    addAndMakeVisible(mIsSoloButton);
    addAndMakeVisible(mNameField);
}

void TrackFieldsComponent::resized()
{
    int width = getWidth();
    int height = getHeight();
    
    mNameField.setBounds(cLeftInset, 0, width - cLeftInset - cRightInset - cIsSoloButtonWidth - cSoloButtonNameFieldPadding, height);
    mIsSoloButton.setBounds(width - cIsSoloButtonWidth - cRightInset, 0, cIsSoloButtonWidth, height);
}

#pragma mark - Button Listener
void TrackFieldsComponent::buttonClicked(Button *button)
{
}

VocalTrack* TrackFieldsComponent::getVocalTrack() const
{
    return mVocalTrack.get();
}
