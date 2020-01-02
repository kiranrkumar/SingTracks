/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Hallelujah_Sample_Midi_mid;
    const int            Hallelujah_Sample_Midi_midSize = 1098;

    extern const char*   moremidi_mid;
    const int            moremidi_midSize = 252;

    extern const char*   OnlyLove_mid;
    const int            OnlyLove_midSize = 57031;

    extern const char*   TestMIDI_mid;
    const int            TestMIDI_midSize = 163;

    extern const char*   testmidi2_mid;
    const int            testmidi2_midSize = 160;

    extern const char*   stIcon_png;
    const int            stIcon_pngSize = 11067;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
