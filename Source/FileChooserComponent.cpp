/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "FileChooserComponent.h"

#include "AppController.h"

//==============================================================================
FileChooserComponent::FileChooserComponent()
{
    addAndMakeVisible(mFilenameBrowser);
    addAndMakeVisible(mConfigureTracksButton);
    
    mFilenameBrowser.addListener(this);
    mConfigureTracksButton.addListener(this);
    
    updateConfigureTracksButtonEnableState();
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
    
    mConfigureTracksButton.setBounds(mConfigureTracksButton.boundsToDraw(localBounds));
    mFilenameBrowser.setBounds(mFilenameBrowser.boundsToDraw(localBounds));
    
    updateConfigureTracksButtonEnableState();
}

void FileChooserComponent::updateConfigureTracksButtonEnableState()
{
    mConfigureTracksButton.setEnabled(AppController::getInstance()->getCurrentFile() != nullptr);
}

#pragma mark - Button Listener
void FileChooserComponent::buttonClicked (Button *button) {
    if (button == &mConfigureTracksButton) {
        printf("'Configure Tracks' button clicked\n");
        AppController::getInstance()->moveToConfigScreen(mMidiFile.getNumTracks());
    }
}

#pragma mark - FilenameComponent Listener
void FileChooserComponent::filenameComponentChanged (FilenameComponent *fileComponent) {
    if (fileComponent == &mFilenameBrowser) {
        File currentFile = fileComponent->getCurrentFile();
        AppController::getInstance()->setCurrentFile(currentFile);
        updateConfigureTracksButtonEnableState();
    }
}
