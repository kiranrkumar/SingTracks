//
//  CustomButtons.hpp
//  SingTracks
//
//  Created by Kiran Kumar on 10/26/19.
//
//
#ifndef CustomButtons_hpp
#define CustomButtons_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class SelfDrawingComponent {
public:
    virtual ~SelfDrawingComponent() {}
    virtual Rectangle<int> boundsToDraw(Rectangle<int>) = 0;
};

class CreateTracksButton : public TextButton, public SelfDrawingComponent {
public:
    CreateTracksButton();
    Rectangle<int> boundsToDraw(Rectangle<int>) override;
private:
    int mWidth;
    int mHeight;
};

class ConfigureTracksButton : public TextButton, public SelfDrawingComponent {
public:
    ConfigureTracksButton();
    Rectangle<int> boundsToDraw(Rectangle<int>) override;
private:
    int mWidth;
    int mHeight;
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
