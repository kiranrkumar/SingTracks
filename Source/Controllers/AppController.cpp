/*
  ==============================================================================

    AppController.cpp
    Created: 22 Dec 2019 10:16:31pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "AppController.h"

#include "MIDITrackSynthesizer.h"
#include "../Model/VocalBusSettings.h"

AppController::AppController() : mMainComponent(nullptr)
{
    mFile.reset(nullptr);
}

AppController::~AppController()
{
    mFile.reset();
    mTrackGenerator.reset();
}

void AppController::createTracks(BusSettingsToBuffersMap &busSettingsToBuffersMap)
{
    mTrackGenerator->renderAudio(busSettingsToBuffersMap);
}

void
AppController::importMidi()
{
    if (mMainComponent != nullptr) {
        int numTracks = mTrackGenerator->getNumTracks();
        const MidiFile midiFile = mTrackGenerator->getMidiFile();
        
        for (int trackIndex = 0; trackIndex < numTracks; ++trackIndex) {
            if (mTrackGenerator->isMusicalTrack(trackIndex)) {
                mVocalTracks.add(new VocalTrack(midiFile, trackIndex));
            }
        }
        
        mMainComponent->setUpConfigScreen(mVocalTracks);
    }
}

void
AppController::setMainComponent(MainComponent *mainComponent)
{
    if (mMainComponent != mainComponent) {
        mMainComponent = mainComponent;
    }
}

MainComponent*
AppController::getMainComponent()
{
    return mMainComponent;
};

File*
AppController::getCurrentFile()
{
    return mFile.get();
}

void
AppController::setCurrentFile(const File &file)
{
    if (mFile.get() != &file) {
        mFile.reset(new File(file));
        std::cout << "File changed to: " << mFile.get()->getFileName() << "\n";
        if (mFile.get() != nullptr) {
            // Create source stream from file
            FileInputStream inStream(*(mFile.get()));
            mTrackGenerator.reset(new TrackGenerator());
            if (mTrackGenerator->readMidiDataFromFile(*(mFile.get()))) {
                mTrackGenerator->printSummary();
            }
            else {
                printf("Uh-oh, didn't read MIDI properly...");
            }
        }
    }
}
