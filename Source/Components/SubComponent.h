/*
  ==============================================================================

    SubComponent.h
    Created: 23 Dec 2019 8:35:18pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class MainComponent;

class SubComponent : public Component
{
public:
    SubComponent(MainComponent *rootComponent);
    MainComponent *getRootComponent();
    
private:
    MainComponent *mRootComponent;
};
