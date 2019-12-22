/*
  ==============================================================================

    TempTestWindow.h
    Created: 21 Dec 2019 5:03:57pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class TempTestWindow : public DocumentWindow
{
public:
    TempTestWindow(String name);
    void closeButtonPressed() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TempTestWindow);
};
