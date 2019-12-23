/*
  ==============================================================================

    AppController.h
    Created: 22 Dec 2019 10:16:31pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "TrackGenerator.hpp"

class AppController
{
public:
    static AppController *getInstance();
    ~AppController();
    
    void createTracksFromFile(std::unique_ptr<File> file);
private:
    AppController();
    static std::unique_ptr<AppController> instance;
    
    TrackGenerator mTrackGenerator;
};
