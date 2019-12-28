/*
  ==============================================================================

    MainComponent.cpp
    Created: 23 Dec 2019 6:37:38pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "MainComponent.h"

#include "../Controllers/AppController.h"
#include "FileChooserComponent.h"
#include "TrackPreviewComponent.h"
#import "../Tests/UnitTestsConfig.h"

MainComponent::MainComponent()
{
    mAppController.reset(new AppController());
    mAppController->setMainComponent(this);
    
    setSize(400, 600);
    mBoundsConstrainer.setMinimumSize(400, 200);
    mCurrentComponent.reset(new FileChooserComponent(this));
    addAndMakeVisible(mCurrentComponent.get());
    mCurrentComponent.get()->setBounds(getLocalBounds());
}

MainComponent::~MainComponent()
{
    mCurrentComponent.reset();
    mAppController.reset();
}

//==============================================================================
void MainComponent::paint (Graphics&)
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        SingTracksUnitTests::runUnitTests();
    });
}

void MainComponent::resized()
{
    Component *currentComponent = mCurrentComponent.get();
    if (currentComponent != nullptr) {
        currentComponent->setBounds(getLocalBounds());
    }
    
    mBoundsConstrainer.checkComponentBounds(this);
}

void MainComponent::setCurrentComponent(Component *component)
{
    if (mCurrentComponent.get() != component) {
        removeAllChildren();
        mCurrentComponent.reset(component);
        addAndMakeVisible(mCurrentComponent.get());
    }
}

void MainComponent::setUpConfigScreen(OwnedArray<VocalTrack> &tracks)
{
    // We shouldn't be here if we're not on the FileChooserComponent screen
    if (dynamic_cast<FileChooserComponent *>(mCurrentComponent.get()) != nullptr) {
        setCurrentComponent(new TrackPreviewComponent(this, tracks));
        mBoundsConstrainer.setMinimumSize(500, 400);
        resized();
    }
}

#pragma mark - Delegate to AppController
File* MainComponent::getCurrentFile()
{
    return mAppController->getCurrentFile();
}

void MainComponent::createTracks()
{
    mAppController->createTracks();
}

void MainComponent::importMidi()
{
    mAppController->importMidi();
}

void MainComponent::setCurrentFile(const File &file)
{
    mAppController->setCurrentFile(file);
}
