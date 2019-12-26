/*
  ==============================================================================

    AppController.cpp
    Created: 22 Dec 2019 10:16:31pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "AppController.h"

#include "MIDITrackSynthesizer.h"

std::unique_ptr<AppController> AppController::instance = std::unique_ptr<AppController>(nullptr);

AppController::AppController() : mMainComponent(nullptr)
{
    mFile.reset(nullptr);
}

AppController::~AppController()
{
    mFile.reset();
    mTrackGenerator.reset();
}

AppController *
AppController::getInstance()
{
    if (instance.get() == nullptr) {
        instance.reset(new AppController());
    }
    
    return instance.get();
}

void
AppController::createTracks()
{
    mTrackGenerator->renderAudio();
}

void
AppController::moveToConfigScreen(int numTracks)
{
    if (mMainComponent != nullptr) {
        mMainComponent->setUpConfigScreen(mTrackGenerator->getNumTracks());
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
AppController::setCurrentFile(File &file)
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
