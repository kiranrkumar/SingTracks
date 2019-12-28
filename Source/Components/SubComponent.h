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

/*
    An immediate child component of the MainComponent. One SubComponent represents a specific screen, within which other controls will exist as children.
 
    Example:
        MainComponent
            -> FileChooserComponent : public SubComponent
                -> FileChooser ("Choose a MIDI file")
                -> TextButton ("Import MIDI")
*/
class SubComponent : public Component
{
public:
    SubComponent(MainComponent *rootComponent);
    MainComponent *getRootComponent();
    
private:
    MainComponent *mRootComponent;
};
