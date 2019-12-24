//
//  CustomButtons.cpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/26/19.
//

#include "CustomButtons.hpp"

#pragma mark - CreateTracksButton
CreateTracksButton::CreateTracksButton() : TextButton("Create Tracks", "Generate audio tracks from MIDI file"), mWidth(250), mHeight(40)
{
}

Rectangle<int>
CreateTracksButton::boundsToDraw(Rectangle<int> localBounds) {
    const int bottomPad = 10;
    
    int localBoundsWidth = localBounds.getWidth();
    int localBoundsHeight = localBounds.getHeight();
    
    int width = std::min(mWidth, localBoundsWidth);
    int height = std::min(mHeight, localBoundsHeight);
    
    int xPos = (localBoundsWidth - width) / 2;
    int yPos = localBoundsHeight - height - bottomPad;
    
    return Rectangle<int>(xPos, yPos, width, height);
}

#pragma mark - ConfigureTracksButton
ConfigureTracksButton::ConfigureTracksButton() : TextButton("Configure Tracks", "Configure settings for tracks to be generated from the MIDI file"), mWidth(250), mHeight(40)
{
}

Rectangle<int>
ConfigureTracksButton::boundsToDraw(Rectangle<int> localBounds) {
    const int bottomPad = 10;
    
    int localBoundsWidth = localBounds.getWidth();
    int localBoundsHeight = localBounds.getHeight();
    
    int width = std::min(mWidth, localBoundsWidth);
    int height = std::min(mHeight, localBoundsHeight);
    
    int xPos = (localBoundsWidth - width) / 2;
    int yPos = localBoundsHeight - height - bottomPad;
    
    return Rectangle<int>(xPos, yPos, width, height);
}

#pragma mark - MIDIFilenameComponent
MIDIFilenameComponent::MIDIFilenameComponent() : FilenameComponent("MIDI File Selector", File(), false, false, false, "*.mid", "", "(Choose a MIDI file)"), mHeight(40)
{
}

Rectangle<int>
MIDIFilenameComponent::boundsToDraw(Rectangle<int> localBounds)
{
    const int horizontalPad = 20;
    
    int localBoundsWidth = localBounds.getWidth();
    int width = std::min(localBoundsWidth - horizontalPad*2, mMaxWidth);
    
    int xPos = (localBoundsWidth - width) / 2;
    int yPos = 100;
    
    return Rectangle<int>(xPos, yPos, width, mHeight);
}
