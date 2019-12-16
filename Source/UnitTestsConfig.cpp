/*
  ==============================================================================

    UnitTestsConfig.cpp
    Created: 15 Dec 2019 9:23:48pm
    Author:  Kiran Kumar

  ==============================================================================
*/

#include "UnitTestsConfig.h"

void SingTracksUnitTests::runUnitTests() {
#if RUN_UNIT_TESTS
    static MIDIReadTest midiTest;
    static TrackGeneratorTest trackTest;
    UnitTestRunner runner;
    runner.runAllTests();
#endif
}

