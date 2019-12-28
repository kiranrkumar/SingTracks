/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "FileChooserComponent.h"

#include "MainComponent.h"
#include "../Controllers/AppController.h"

//==============================================================================
FileChooserComponent::FileChooserComponent(MainComponent *mainComponent) : SubComponent::SubComponent(mainComponent)
{
    addAndMakeVisible(mFilenameBrowser);
    addAndMakeVisible(mImportMidiButton);
    
    mFilenameBrowser.addListener(this);
    mImportMidiButton.addListener(this);
    
    updateImportMidiButtonEnableState();
}

FileChooserComponent::~FileChooserComponent()
{
}

//==============================================================================
void FileChooserComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Select a MIDI File", getLocalBounds(), Justification::centredTop, true);
}

void FileChooserComponent::resized()
{
    Rectangle<int> localBounds = getLocalBounds();
    
    mImportMidiButton.setBounds(mImportMidiButton.boundsToDraw(localBounds));
    mFilenameBrowser.setBounds(mFilenameBrowser.boundsToDraw(localBounds));
    
    updateImportMidiButtonEnableState();
}

void FileChooserComponent::updateImportMidiButtonEnableState()
{
    if (getRootComponent() != nullptr) {
        mImportMidiButton.setEnabled(getRootComponent()->getCurrentFile() != nullptr);
    }
}

#pragma mark - Button Listener
void FileChooserComponent::buttonClicked (Button *button) {
    if (button == &mImportMidiButton) {
        printf("'Import MIDI' button clicked\n");
        if (getRootComponent() != nullptr) {
            getRootComponent()->importMidi();
        }
    }
}

#pragma mark - FilenameComponent Listener
void FileChooserComponent::filenameComponentChanged (FilenameComponent *fileComponent) {
    if (fileComponent == &mFilenameBrowser && getRootComponent() != nullptr) {
        File currentFile = fileComponent->getCurrentFile();
        getRootComponent()->setCurrentFile(currentFile);
        updateImportMidiButtonEnableState();
    }
}
