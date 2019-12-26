/*
  ==============================================================================

    TrackPreviewComponent.h
    Created: 21 Dec 2019 4:51:01pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomButtons.hpp"
#include "TrackFieldsComponent.h"

class TrackPreviewComponent : public Component, private Button::Listener
{
public:
    TrackPreviewComponent();
    ~TrackPreviewComponent();
    
    void paint (Graphics&) override;
    void resized() override;

private:
    void buttonClicked(Button *) override;
    
    void setUpTrackFields(int numComponents); // KRK_FIXME will expand this to include necessary information (track names, maybe duration, etc)
    
    Component mTrackFieldsContainer;
    OwnedArray<TrackFieldsComponent> mTrackFields;
    Viewport mTrackFieldsContainerViewport;
    
    CreateTracksButton mCreateTracksButton;
};
