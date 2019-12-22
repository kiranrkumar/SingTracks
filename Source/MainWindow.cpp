/*
  ==============================================================================

    MainWindow.cpp
    Created: 16 Dec 2019 10:42:05pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "MainWindow.h"
#include "FileChooserComponent.h"

MainWindow::MainWindow(String name) : DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setContentOwned(new FileChooserComponent(), true);
    
#if JUCE_IOS || JUCE_ANDROID
    setFullScreen(true);
#else
    setResizable(true, true);
    centreWithSize(getWidth(), getHeight());
#endif
    setVisible(true);
}

void MainWindow::closeButtonPressed()
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}
