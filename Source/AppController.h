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
    
    File* getCurrentFile();
    void setCurrentFile(File&);
    void createTracks();
private:
    static std::unique_ptr<AppController> instance;
    
    AppController();
    std::unique_ptr<File> mFile;
};
