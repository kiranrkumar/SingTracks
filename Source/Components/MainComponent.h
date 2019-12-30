/*
  ==============================================================================

    MainComponent.h
    Created: 23 Dec 2019 6:37:37pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomButtons.hpp"
#include "../Controllers/TrackGenerator.hpp"

class AppController;
class SubComponent;
class VocalTrack;
class VocalGroupBus;

//==============================================================================
/*
    This is the top-level/root component of the app. Different screens exist as fullscreen children of MainComponent. Those immediate children have their own children for the UI elements that the user will see and interact with
*/
class MainComponent : public Component
{
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void setCurrentComponent(SubComponent *);
    
    void setUpConfigScreen(OwnedArray<VocalTrack> &);
    
    // Delegate to AppController
    File* getCurrentFile();
    void createTracks();
    void createTracks(OwnedArray<VocalGroupBus>& busses, OwnedArray<VocalTrack> &tracks);
    void importMidi();
    void setCurrentFile(const File &);

private:
    std::unique_ptr<AppController> mAppController;
    std::unique_ptr<SubComponent> mCurrentComponent;
    ComponentBoundsConstrainer mBoundsConstrainer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
