/*
  ==============================================================================

    TrackPreviewComponent.h
    Created: 21 Dec 2019 4:51:01pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "CustomButtons.hpp"
#include "SubComponent.h"
#include "TrackFieldsComponent.h"

class MainComponent;
class VocalTrack;
class TrackSettingsComponent;

class TrackPreviewComponent : public SubComponent, private Button::Listener
{
public:
    TrackPreviewComponent(MainComponent *component, OwnedArray<VocalTrack> &tracks);
    
    void paint (Graphics&) override;
    void resized() override;

private:
    void buttonClicked(Button *) override;
    
    Component mTrackFieldsContainer;
    OwnedArray<TrackFieldsComponent> mTrackFields;
    Viewport mTrackFieldsContainerViewport;
    OwnedArray<TrackSettingsComponent> mTrackSettings;
    CreateTracksButton mCreateTracksButton;
};
