/*
  ==============================================================================

    TrackPreviewComponent.cpp
    Created: 21 Dec 2019 4:51:01pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TrackPreviewComponent.h"
#include "AppController.h"

const int cVerticalSpacePerTrackField = 50;
const int cTrackFieldContainerTopInset = 20;

TrackPreviewComponent::TrackPreviewComponent()
{
    setSize(600, 700);
    
    addAndMakeVisible(mTrackFieldsContainer);
    setUpTrackFields(8); // KRK_FIXME placeholder value - will eventually be based on actual number of tracks
    
    addAndMakeVisible(mTrackFieldsContainerViewport);
    mTrackFieldsContainerViewport.setViewedComponent(&mTrackFieldsContainer, false);
    
    addAndMakeVisible(mCreateTracksButton);
    mCreateTracksButton.addListener(this);
    
    layoutSubComponents();
}

TrackPreviewComponent::~TrackPreviewComponent()
{
    
}

void TrackPreviewComponent::paint(Graphics &g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void TrackPreviewComponent::resized()
{
    layoutSubComponents();
}

#pragma mark - Button Listener

void TrackPreviewComponent::buttonClicked(Button *button)
{
    if (button == &mCreateTracksButton) {
        AppController::getInstance()->createTracks();
    }
}

void TrackPreviewComponent::layoutSubComponents()
{
    int numComponents = mTrackFields.size();
    mTrackFieldsContainer.setBounds(0, 0, getWidth(), cTrackFieldContainerTopInset + numComponents * cVerticalSpacePerTrackField);
    
    // Track field components are child components of mTrackFieldsContainer
    for (int i = 0; i < numComponents; ++i) {
        TrackFieldsComponent *tfc = mTrackFields[i];
        tfc->setBounds(0, cTrackFieldContainerTopInset + i * cVerticalSpacePerTrackField, getWidth(), 35);
    }
    
    // Limit track fields view to the top of the overall component
    mTrackFieldsContainerViewport.setBounds(0, 0, getWidth(), 350);
    
    mCreateTracksButton.setBounds(mCreateTracksButton.boundsToDraw(getLocalBounds()));
}

void TrackPreviewComponent::setUpTrackFields(int numComponents)
{
    if (mTrackFields.size() > 0) {
        return;
    }
    
    for (int i = 0; i < numComponents; ++i) {
        TrackFieldsComponent *tfc = new TrackFieldsComponent();
        mTrackFields.add(tfc);
        mTrackFieldsContainer.addAndMakeVisible(tfc);
    }
}
