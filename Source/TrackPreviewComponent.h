/*
  ==============================================================================

    TrackPreviewComponent.h
    Created: 21 Dec 2019 4:51:01pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TrackPreviewComponent : public Component, private Button::Listener
{
public:
    TrackPreviewComponent();
    ~TrackPreviewComponent();

private:
    void buttonClicked(Button *) override;
};
