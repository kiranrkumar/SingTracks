//
//  CustomButtons.hpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/26/19.
//
//
#ifndef CustomButtons_hpp
#define CustomButtons_hpp

#include "../../JuceLibraryCode/JuceHeader.h"

class SelfDrawingComponent {
public:
    virtual ~SelfDrawingComponent() {}
    virtual Rectangle<int> boundsToDraw(Rectangle<int>) = 0;
};

class BottomButton : public TextButton, SelfDrawingComponent {
public:
    BottomButton(const String &name, const String &description);
    Rectangle<int> boundsToDraw(Rectangle<int>);
private:
    int mWidth;
    int mHeight;
};

class ImportMidiButton : public BottomButton {
public:
    ImportMidiButton();
};

class CreateTracksButton : public BottomButton {
public:
    CreateTracksButton();
};

class MIDIFilenameComponent : public FilenameComponent, public SelfDrawingComponent {
public:
    MIDIFilenameComponent();
    Rectangle<int> boundsToDraw(Rectangle<int>) override;
private:
    const int mMaxWidth = 800;
    int mHeight;
};

#endif /* CustomButtons_hpp */
