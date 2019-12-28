/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "FileChooserComponent.h"

#include "../Controllers/AppController.h"

//==============================================================================
FileChooserComponent::FileChooserComponent()
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
    mImportMidiButton.setEnabled(AppController::getInstance()->getCurrentFile() != nullptr);
}

#pragma mark - Button Listener
void FileChooserComponent::buttonClicked (Button *button) {
    if (button == &mImportMidiButton) {
        printf("'Import MIDI' button clicked\n");
        AppController::getInstance()->importMidi();
    }
}

#pragma mark - FilenameComponent Listener
void FileChooserComponent::filenameComponentChanged (FilenameComponent *fileComponent) {
    if (fileComponent == &mFilenameBrowser) {
        File currentFile = fileComponent->getCurrentFile();
        AppController::getInstance()->setCurrentFile(currentFile);
        updateImportMidiButtonEnableState();
    }
}
