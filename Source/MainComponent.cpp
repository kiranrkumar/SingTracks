/*
  ==============================================================================

    MainComponent.cpp
    Created: 23 Dec 2019 6:37:38pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "MainComponent.h"

#include "FileChooserComponent.h"
#include "TrackPreviewComponent.h"

MainComponent::MainComponent()
{
    setSize(400, 600);
    mBoundsConstrainer.setMinimumSize(400, 200);
    mCurrentComponent.reset(new FileChooserComponent());
    addAndMakeVisible(mCurrentComponent.get());
    mCurrentComponent.get()->setBounds(getLocalBounds());
}

MainComponent::~MainComponent()
{
    mCurrentComponent.reset();
}

//==============================================================================
void MainComponent::paint (Graphics&)
{
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
        mCurrentComponent.reset(component);
    }
}
