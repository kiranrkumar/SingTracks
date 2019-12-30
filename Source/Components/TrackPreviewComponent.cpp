/*
  ==============================================================================

    TrackPreviewComponent.cpp
    Created: 21 Dec 2019 4:51:01pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TrackPreviewComponent.h"

#include "MainComponent.h"
#include "TrackSettingsComponent.h"
#include "../Model/VocalTrack.h"

const int cVerticalSpacePerTrackField = 40;
const int cTrackFieldContainerTopInset = 20;

TrackPreviewComponent::TrackPreviewComponent(MainComponent *mainComponent, OwnedArray<VocalTrack> &tracks) : SubComponent::SubComponent(mainComponent)
{
    // Fields for each track (name, is solo, etc)
    for (int i = 0; i < tracks.size(); ++i) {
        TrackFieldsComponent *tfc = new TrackFieldsComponent(tracks.removeAndReturn(i));
        mTrackFields.add(tfc);
        mTrackFieldsContainer.addAndMakeVisible(tfc);
    }
    
    addAndMakeVisible(mTrackFieldsContainer);
    
    std::vector<String> settingsNames = {"Primary", "Solo/Harmony", "Background"};
    for (int i = 0; i < settingsNames.size(); ++i) {
        TrackSettingsComponent *tsc = new TrackSettingsComponent(settingsNames[i]);
        mTrackSettings.add(tsc);
        addAndMakeVisible(tsc);
    }
    
    addAndMakeVisible(mTrackFieldsContainerViewport);
    mTrackFieldsContainerViewport.setViewedComponent(&mTrackFieldsContainer, false);
    
    addAndMakeVisible(mCreateTracksButton);
    mCreateTracksButton.addListener(this);
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
        tfc->setBounds(0, cTrackFieldContainerTopInset + i * cVerticalSpacePerTrackField, getWidth(), 25);
    }
    
    Rectangle<int> area = getLocalBounds();
    // Limit track fields view to the top of the overall component
    mTrackFieldsContainerViewport.setBounds(area.removeFromTop(200));
    
    int trackSettingsWidth = getWidth() / mTrackSettings.size();
    area = area.removeFromTop(area.getHeight() - 50);
    for (int i = 0; i < mTrackSettings.size(); ++i) {
        TrackSettingsComponent *tsc = mTrackSettings[i];
        tsc->setBounds(i * trackSettingsWidth, area.getY(), trackSettingsWidth, area.getHeight());
    }
    
    mCreateTracksButton.setBounds(mCreateTracksButton.boundsToDraw(getLocalBounds()));
}
#pragma mark - Private -
#pragma mark Button Listener
void TrackPreviewComponent::buttonClicked(Button *button)
{
    if (button == &mCreateTracksButton && getRootComponent() != nullptr) {
        getRootComponent()->createTracks();
    
//  USE THE BELOW ONCE WE'RE READY TO SWITCH TO THE NEW RENDER CALLS

//        // Collect group busses containing current gain and pan information
//        OwnedArray<VocalBusSettings> busSettingsArray;
//        for (TrackSettingsComponent *settingsComp : mTrackSettings) {
//            busSettingsArray.add(new VocalBusSettings(settingsComp->getBusSettings()));
//        }

        

//        getRootComponent()->createTracks(busSettingsArray, OwnedArray<VocalTrack> &tracks);
        
    }
}
