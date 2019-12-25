/*
  ==============================================================================

    UnitTestsConfig.h
    Created: 15 Dec 2019 9:21:24pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#pragma once

const bool RUN_UNIT_TESTS = 1;

#include "MidiFile_TEST.h"
#include "TrackGenerator_TEST.h"

class SingTracksUnitTests {
public:
    static void runUnitTests();
};
