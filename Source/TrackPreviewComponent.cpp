/*
  ==============================================================================

    TrackPreviewComponent.cpp
    Created: 21 Dec 2019 4:51:01pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TrackPreviewComponent.h"

TrackPreviewComponent::TrackPreviewComponent()
{
    setSize(600, 700);
    addAndMakeVisible(mTrackField);
    addAndMakeVisible(mTrackField2);
}

TrackPreviewComponent::~TrackPreviewComponent()
{
    
}

void TrackPreviewComponent::paint(Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void TrackPreviewComponent::resized()
{
    mTrackField.setBounds(0, 150, getWidth(), 30);
    mTrackField2.setBounds(0, 200, getWidth(), 30);
}

#pragma mark - Button Listener

void TrackPreviewComponent::buttonClicked(Button *button)
{
    
}
