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
const int cTrackFieldHeight = 25;
const int cTrackFieldContainerTopInset = 20;

TrackPreviewComponent::TrackPreviewComponent(MainComponent *mainComponent, OwnedArray<VocalTrack> &tracks) : SubComponent::SubComponent(mainComponent)
{
    // Fields for each track (name, isSolo, etc)
    while (!tracks.isEmpty()) {
        TrackFieldsComponent *tfc = new TrackFieldsComponent(tracks.removeAndReturn(0));
        mTrackFields.add(tfc);
        mTrackFieldsContainer.addAndMakeVisible(tfc);
    }
    
    addAndMakeVisible(mTrackFieldsContainer);
    
    std::vector<String> settingsNames = { VocalBusStrings::PRIMARY, VocalBusStrings::SOLO_HARMONY, VocalBusStrings::BACKGROUND };
    for (int i = 0; i < NumBusses; ++i) {
        TrackSettingsComponent *tsc = new TrackSettingsComponent(VocalBus(i));
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
    // Draw from bottom up since the top section will be the one that's height variable
    
    Rectangle<int> area = getLocalBounds();
    
    // "Create Tracks" button
    const int buttonHeight = 50;
    Rectangle<int> areaForButton = area.removeFromBottom(buttonHeight);
    mCreateTracksButton.setBounds(mCreateTracksButton.boundsToDraw(areaForButton));
    
    // Track settings (volume, pan)
    const int trackSettingsHeight = 150;
    Rectangle<int> areaForSettings = area.removeFromBottom(trackSettingsHeight);
    int numTrackSettings = mTrackSettings.size();
    int trackSettingsWidth = areaForSettings.getWidth() / numTrackSettings;
    for (int i = 0; i < numTrackSettings; ++i) {
        TrackSettingsComponent *tsc = mTrackSettings[i];
        tsc->setBounds(i * trackSettingsWidth, areaForSettings.getY(), trackSettingsWidth, areaForSettings.getHeight());
    }
    
    // List of track fields (name, isSolo, etc)
    int numFields = mTrackFields.size();
    
    // The track fields container is sized to fit all fields, but the viewport remains fixed at the remaining area within the TrackPreviewComponent (viewport provides scrollbar as needed)
    mTrackFieldsContainer.setBounds(0, 0, getWidth(), cTrackFieldContainerTopInset + numFields * cVerticalSpacePerTrackField);
    mTrackFieldsContainerViewport.setBounds(area);
    
    for (int i = 0; i < numFields; ++i) {
        TrackFieldsComponent *tfc = mTrackFields[i];
        tfc->setBounds(0, cTrackFieldContainerTopInset + i * cVerticalSpacePerTrackField, getWidth(), cTrackFieldHeight);
    }
}

#pragma mark - Private -
#pragma mark Button Listener
void TrackPreviewComponent::buttonClicked(Button *button)
{
    if (button == &mCreateTracksButton && getRootComponent() != nullptr) {
    
        // Map bus to vocal settings
        BusToSettingsMap busToSettingsMap;
        for (TrackSettingsComponent *settingsComp : mTrackSettings) {
            const VocalBusSettings& busSettings = settingsComp->getBusSettings();
            busToSettingsMap[busSettings.getBus()] = std::make_unique<VocalBusSettings>(VocalBusSettings(busSettings));
        }
        
        // Map bus to Vocal Tracks
        BusToTracksMap busToTracksMap;
        for (TrackFieldsComponent *fieldsComp : mTrackFields) {
            VocalTrack *track = fieldsComp->getVocalTrack();
            busToTracksMap[track->getBus()].push_back(track);
        }

        getRootComponent()->createTracks(busToSettingsMap, busToTracksMap);
        
    }
}
