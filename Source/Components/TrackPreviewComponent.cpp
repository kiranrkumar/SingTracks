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
        // KRK_FIXME lots of copying going on. Could stand to optimize
        
        // Create a temp map of bus to bus settings
        std::map<VocalBus, VocalBusSettings> busToSettingsMap;
        for (TrackSettingsComponent *settingsComp : mTrackSettings) {
            const VocalBusSettings& busSettings = settingsComp->getBusSettings();
            busToSettingsMap[busSettings.getBus()] = busSettings;
        }
        
        // Use the above map to help map bus settings directly to the audio buffers using the same bus
        BusSettingsToBuffersMap busSettingsToBuffersMap;
        for (TrackFieldsComponent *fieldsComp : mTrackFields) {
            VocalTrack *track = fieldsComp->getVocalTrack();
            const VocalBusSettings &settings = busToSettingsMap[track->getBus()];
            std::unique_ptr<VocalBusSettings> settingsForBus = std::make_unique<VocalBusSettings>(VocalBusSettings(settings));
            busSettingsToBuffersMap[std::move(settingsForBus)].push_back(AudioBuffer<float>( track->getBuffer()));
        }

        getRootComponent()->createTracks(busSettingsToBuffersMap);
        
    }
}
