/*
  ==============================================================================

    AudioDefines.h
    Created: 30 Dec 2019 11:05:16am
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class VocalBusSettings;

typedef enum {
    Solo = 0,
    Background,
    Primary,
    
    NumBusses
} VocalBus;

namespace VocalBusStrings {
    const String SOLO_HARMONY("Solo/Harmony");
    const String BACKGROUND("Background");
    const String PRIMARY("Primary");
}

const std::map<const String, VocalBus> DisplayNameToBusMap = {
    { VocalBusStrings::SOLO_HARMONY, Solo },
    { VocalBusStrings::BACKGROUND, Background },
    { VocalBusStrings::PRIMARY, Background }
};

const std::map<VocalBus, const String> BusToDisplayName = {
    {Solo, VocalBusStrings::SOLO_HARMONY},
    {Background, VocalBusStrings::BACKGROUND},
    {Primary, VocalBusStrings::PRIMARY},
};

typedef std::map<std::unique_ptr<VocalBusSettings>, std::vector<AudioBuffer<float>>> BusSettingsToBuffersMap;

