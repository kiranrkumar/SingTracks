/*
  ==============================================================================

    AppController.h
    Created: 22 Dec 2019 10:16:31pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../Components/MainComponent.h"
#include "TrackGenerator.hpp"
#include "../Model/VocalTrack.h"

class AppController
{
public:
    AppController();
    ~AppController();
    
    void setMainComponent(MainComponent *);
    MainComponent* getMainComponent();
    
    File* getCurrentFile();
    void setCurrentFile(const File&);
    void createTracks();
    
    void importMidi();
    
private:
    std::unique_ptr<File> mFile;
    MainComponent *mMainComponent;
    std::unique_ptr<TrackGenerator> mTrackGenerator;
    std::vector<VocalTrack> mVocalTracks;
};
