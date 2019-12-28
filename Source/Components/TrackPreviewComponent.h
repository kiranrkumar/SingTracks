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
#include "TrackFieldsComponent.h"
#include "TrackSettingsComponent.h"

class MainComponent;
class VocalTrack;

class TrackPreviewComponent : public Component, private Button::Listener
{
public:
    TrackPreviewComponent(MainComponent *component, OwnedArray<VocalTrack> &tracks);
    
    void paint (Graphics&) override;
    void resized() override;

private:
    void buttonClicked(Button *) override;
    
    MainComponent *mMainComponent;
    Component mTrackFieldsContainer;
    OwnedArray<TrackFieldsComponent> mTrackFields;
    Viewport mTrackFieldsContainerViewport;
    
    OwnedArray<TrackSettingsComponent> mTrackSettings;
    
    CreateTracksButton mCreateTracksButton;
};
