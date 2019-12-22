/*
  ==============================================================================

    TempTestWindow.cpp
    Created: 21 Dec 2019 5:03:57pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "TempTestWindow.h"

#include "TrackPreviewComponent.h"

TempTestWindow::TempTestWindow(String name) : DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentOwned(new TrackPreviewComponent(), true);
    
#if JUCE_IOS || JUCE_ANDROID
    setFullScreen(true);
#else
    setResizable(true, true);
    centreWithSize(getWidth(), getHeight());
#endif
    setVisible(true);
}

void TempTestWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
