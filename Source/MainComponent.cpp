/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

#include "TrackGenerator.hpp"
#include "MidiFile_TEST.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    mBoundsConstrainer.setMinimumSize(500, 300);
    
    addAndMakeVisible(mFilenameBrowser);
    addAndMakeVisible(mCreateTracksButton);
    mCreateTracksButton.addListener(this);
    mFilenameBrowser.addListener(this);
    
    mSelectedFile = nullptr;
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Select a MIDI File", getLocalBounds(), Justification::centredTop, true);
    
#if RUN_UNIT_TESTS
    static MIDIReadTest midiTest;
    UnitTestRunner runner;
    runner.runAllTests();
#endif
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    Rectangle<int> localBounds = getLocalBounds();
    
    mCreateTracksButton.setBounds(mCreateTracksButton.boundsToDraw(localBounds));
    mFilenameBrowser.setBounds(mFilenameBrowser.boundsToDraw(localBounds));
    
    mBoundsConstrainer.checkComponentBounds(this);
}

#pragma mark - Button Listener
void MainComponent::buttonClicked (Button *button) {
    printf("Button clicked\n");
    
    if (mSelectedFile != nullptr) {
    // Create source stream from file
        FileInputStream inStream(*mSelectedFile);
        bool didRead = mTrackGenerator.getMidiDataFromFile(*mSelectedFile);
        if (didRead) {
            mTrackGenerator.printSummary();
//            mTrackGenerator.fillMidiBuffer();
            mTrackGenerator.renderAllMidiTracks();
        }
        else {
            printf("Uh-oh, didn't read MIDI properly...");
        }
    }
}

#pragma mark - FilenameComponent Listener
void MainComponent::filenameComponentChanged (FilenameComponent *fileComponent) {
    if (fileComponent == &mFilenameBrowser) {
        std::cout << "File changed to: " << fileComponent->getCurrentFile().getFileName() << "\n";
        
        // KRK_FIXME is there a cleaner way to do this?
        delete mSelectedFile;
        mSelectedFile = new File(fileComponent->getCurrentFile());
    }
}
