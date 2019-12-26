/*
  ==============================================================================

    MainComponent.cpp
    Created: 23 Dec 2019 6:37:38pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "MainComponent.h"

#include "AppController.h"
#include "FileChooserComponent.h"
#include "TrackPreviewComponent.h"
#import "UnitTestsConfig.h"

MainComponent::MainComponent()
{
    setSize(400, 600);
    mBoundsConstrainer.setMinimumSize(400, 200);
    mCurrentComponent.reset(new FileChooserComponent());
    addAndMakeVisible(mCurrentComponent.get());
    mCurrentComponent.get()->setBounds(getLocalBounds());
    
    AppController::getInstance()->setMainComponent(this);
}

MainComponent::~MainComponent()
{
    mCurrentComponent.reset();
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

void MainComponent::setUpConfigScreen(int numTracks)
{
    // We shouldn't be here if we're not on the FileChooserComponent screen
    if (dynamic_cast<FileChooserComponent *>(mCurrentComponent.get()) != nullptr) {
        setCurrentComponent(new TrackPreviewComponent(numTracks));
        mBoundsConstrainer.setMinimumSize(400, 400);
        resized();
    }
}
