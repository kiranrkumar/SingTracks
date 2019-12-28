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
    TrackFieldsComponent(VocalTrack &);
    ~TrackFieldsComponent();
    
    void paint(Graphics&) override;
    void resized() override;
    
    void buttonClicked(Button*) override;
    
private:
    ToggleButton mIsSoloButton;
    TextEditor mNameField;
};
