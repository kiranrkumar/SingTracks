/*
  ==============================================================================

    VocalTrack.cpp
    Created: 27 Dec 2019 5:21:33pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "VocalTrack.h"

VocalTrack::VocalTrack(const MidiFile &midiFile, int trackNum)
{
    std::string displayName;
    displayName += "Midi track "; // KRK_TEMP
    displayName += std::to_string(trackNum);
    mDisplayName = String(displayName);
}

String VocalTrack::getDisplayName()
{
    return mDisplayName;
}
