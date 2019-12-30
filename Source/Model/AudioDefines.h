/*
  ==============================================================================

    AudioDefines.h
    Created: 30 Dec 2019 11:05:16am
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

typedef enum {
    Solo,
    Background
} VocalBus;

namespace VocalBusStrings {
    const String SOLO_HARMONY("Solo/Harmony");
    const String BACKGROUND("Background");
    const String PRIMARY("Primary");
}

const std::map<String, VocalBus> DisplayNameToBusMap = {
    { VocalBusStrings::SOLO_HARMONY, Solo },
    { VocalBusStrings::BACKGROUND, Background },
    { VocalBusStrings::PRIMARY, Background }
};

