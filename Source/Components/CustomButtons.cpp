//
//  CustomButtons.cpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/26/19.
//

#include "CustomButtons.hpp"

#pragma mark - BottomButton
BottomButton::BottomButton(const String &name, const String &description) : TextButton(name, description), mWidth(250), mHeight(40)
{
}

Rectangle<int>
BottomButton::boundsToDraw(Rectangle<int> localBounds) {
    const int bottomPad = 10;
    
    int localBoundsWidth = localBounds.getWidth();
    int localBoundsHeight = localBounds.getHeight();
    
    int width = std::min(mWidth, localBoundsWidth);
    int height = std::min(mHeight, localBoundsHeight);
    
    int xPos = (localBoundsWidth - width) / 2;
    int yPos = localBounds.getY() + localBoundsHeight - height - bottomPad;
    
    return Rectangle<int>(xPos, yPos, width, height);
}

#pragma mark - ImportMidiButton
ImportMidiButton::ImportMidiButton() : BottomButton("Import MIDI", "Import the selected MIDI File")
{
}

#pragma mark - CreateTracksButton
CreateTracksButton::CreateTracksButton() : BottomButton("Create Tracks", "Generate audio tracks from MIDI file")
{
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
