/*
  ==============================================================================

    TrackPreviewComponent.h
    Created: 21 Dec 2019 4:51:01pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
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
    TrackFieldsComponent mTrackField;
    TrackFieldsComponent mTrackField2;
};
