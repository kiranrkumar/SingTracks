/*
  ==============================================================================

    SubComponent.h
    Created: 23 Dec 2019 8:35:18pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class SubComponent : Component
{
public:
    SubComponent();
    virtual ~SubComponent();
    
    void setRootComponent(Component *);
    Component *getRootComponent();
    
private:
    std::unique_ptr<Component> mRootComponent;
};
