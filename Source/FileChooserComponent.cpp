/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "FileChooserComponent.h"

#include "AppController.h"
//#include "TrackGenerator.hpp"
#include "UnitTestsConfig.h"

//==============================================================================
FileChooserComponent::FileChooserComponent()
{
    setSize (600, 400);
    mBoundsConstrainer.setMinimumSize(500, 300);
    
    addAndMakeVisible(mFilenameBrowser);
    addAndMakeVisible(mCreateTracksButton);
    mCreateTracksButton.addListener(this);
    mFilenameBrowser.addListener(this);
    
    mSelectedFile = nullptr;
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
    
    mCreateTracksButton.setBounds(mCreateTracksButton.boundsToDraw(localBounds));
    mFilenameBrowser.setBounds(mFilenameBrowser.boundsToDraw(localBounds));
    
    mBoundsConstrainer.checkComponentBounds(this);
}

#pragma mark - Button Listener
void FileChooserComponent::buttonClicked (Button *button) {
    if (button == &mCreateTracksButton && mSelectedFile != nullptr) {
        printf("'Create Tracks' button clicked\n");
        AppController::getInstance()->createTracksFromFile(std::move(mSelectedFile));
    }
}

#pragma mark - FilenameComponent Listener
void FileChooserComponent::filenameComponentChanged (FilenameComponent *fileComponent) {
    if (fileComponent == &mFilenameBrowser) {
        std::cout << "File changed to: " << fileComponent->getCurrentFile().getFileName() << "\n";
        
        // KRK_FIXME is there a cleaner way to do this?
        mSelectedFile.reset(new File(fileComponent->getCurrentFile()));
    }
}
