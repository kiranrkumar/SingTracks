/*
  ==============================================================================

    SubComponent.cpp
    Created: 23 Dec 2019 8:35:18pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "MainComponent.h"
#include "SubComponent.h"

SubComponent::SubComponent(MainComponent *rootComponent)
{
    mRootComponent = rootComponent;
}

MainComponent * SubComponent::getRootComponent()
{
    return mRootComponent;
}
