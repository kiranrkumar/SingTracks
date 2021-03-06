/*
  ==============================================================================

    TrackFieldsComponent.h
    Created: 21 Dec 2019 10:10:48pm
    Author:  Kiran Kumar
 
    Hold fields for a single track (name, isSolo, etc)

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class VocalTrack;

class TrackFieldsComponent : public Component, private Button::Listener
{
public:
    TrackFieldsComponent();
    TrackFieldsComponent(VocalTrack *);
    
    void resized() override;
    void buttonClicked(Button*) override;
    
    VocalTrack* getVocalTrack() const;
    
private:
    std::unique_ptr<VocalTrack> mVocalTrack;
    ToggleButton mIsSoloButton;
    TextEditor mNameField;
};
