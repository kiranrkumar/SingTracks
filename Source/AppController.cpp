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

AppController::AppController() {}
AppController::~AppController() {}

AppController *
AppController::getInstance()
{
    if (instance.get() == nullptr) {
        instance.reset(new AppController());
    }
    
    return instance.get();
}

void
AppController::createTracksFromFile(std::unique_ptr<File> file)
{
    printf("AppController::createTracksFromFile\n");
    TrackGenerator trackGenerator;
    // Create source stream from file
    FileInputStream inStream(*(file.get()));
    bool didRead = trackGenerator.readMidiDataFromFile(*(file.get()));
    if (didRead) {
        trackGenerator.printSummary();
        trackGenerator.renderAudio();
    }
    else {
        printf("Uh-oh, didn't read MIDI properly...");
    }
}
