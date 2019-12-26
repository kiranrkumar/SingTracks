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

/*
    KRK_FIXME - numTracks as passed in below will have an extra track if it's a multitrack MIDI file create in Logic (maybe some other programs as well) because Logic adds the additional metadata track at the beginning. Need a way to filter this non-musical track out as necessary
*/
TrackPreviewComponent::TrackPreviewComponent(int numTracks) : mNumTracks(numTracks)
{
    addAndMakeVisible(mTrackFieldsContainer);
    setUpTrackFields(mNumTracks); // KRK_FIXME placeholder value - will eventually be based on actual number of tracks
    
    addAndMakeVisible(mTrackFieldsContainerViewport);
    mTrackFieldsContainerViewport.setViewedComponent(&mTrackFieldsContainer, false);
    
    addAndMakeVisible(mCreateTracksButton);
    mCreateTracksButton.addListener(this);
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

#pragma mark - Button Listener
void TrackPreviewComponent::buttonClicked(Button *button)
{
    if (button == &mCreateTracksButton) {
        AppController::getInstance()->createTracks();
    }
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
