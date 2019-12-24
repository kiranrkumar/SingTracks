/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "FileChooserComponent.h"

#include "AppController.h"
#include "UnitTestsConfig.h"

//==============================================================================
FileChooserComponent::FileChooserComponent()
{
    setSize (600, 400);
    mBoundsConstrainer.setMinimumSize(500, 300);
    
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
    
    SingTracksUnitTests::runUnitTests();
}

void FileChooserComponent::resized()
{
    // This is called when the FileChooserComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    Rectangle<int> localBounds = getLocalBounds();
    
    mConfigureTracksButton.setBounds(mConfigureTracksButton.boundsToDraw(localBounds));
    mFilenameBrowser.setBounds(mFilenameBrowser.boundsToDraw(localBounds));
    
    mBoundsConstrainer.checkComponentBounds(this);
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
