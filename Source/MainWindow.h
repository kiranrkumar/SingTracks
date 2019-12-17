/*
  ==============================================================================

    MainWindow.h
    Created: 16 Dec 2019 10:42:05pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MainWindow : public DocumentWindow
{
public:
    MainWindow(String name);
    void closeButtonPressed() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow);
};
