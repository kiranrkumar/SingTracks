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
class VocalTrack;

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void setCurrentComponent(Component *);
    
    void setUpConfigScreen(OwnedArray<VocalTrack> &);
    
    // Delegate to AppController
    File* getCurrentFile();
    void createTracks();
    void importMidi();
    void setCurrentFile(const File &);

private:
    std::unique_ptr<AppController> mAppController;
    std::unique_ptr<Component> mCurrentComponent;
    ComponentBoundsConstrainer mBoundsConstrainer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
