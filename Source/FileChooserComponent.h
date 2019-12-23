/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomButtons.hpp"
#include "TrackGenerator.hpp"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class FileChooserComponent   : public Component, private Button::Listener, private FilenameComponentListener
{
public:
    //==============================================================================
    FileChooserComponent();
    ~FileChooserComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void buttonClicked (Button*) override;
    void filenameComponentChanged (FilenameComponent *) override;
    
    //==============================================================================
    // Your private member variables go here...
    MIDIFilenameComponent mFilenameBrowser;
    CreateTracksButton mCreateTracksButton;
    ComponentBoundsConstrainer mBoundsConstrainer;
    TrackGenerator mTrackGenerator;
    
    std::unique_ptr<File> mSelectedFile;
    MidiFile mMidiFile;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileChooserComponent)
};
