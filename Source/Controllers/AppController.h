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

class AppController
{
public:
    static AppController *getInstance();
    ~AppController();
    
    void setMainComponent(MainComponent *);
    MainComponent* getMainComponent();
    
    File* getCurrentFile();
    void setCurrentFile(File&);
    void createTracks();
    
    void moveToConfigScreen(int numTracks); // KRK_FIXME - this seems really inflexible, but I'm just trying it for now. May generalize/clean up a bit later
    
private:
    static std::unique_ptr<AppController> instance;
    
    AppController();
    std::unique_ptr<File> mFile;
    MainComponent *mMainComponent;
    std::unique_ptr<TrackGenerator> mTrackGenerator;
};
