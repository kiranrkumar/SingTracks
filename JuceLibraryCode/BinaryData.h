/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   Hallelujah_Sample_Midi_mid;
    const int            Hallelujah_Sample_Midi_midSize = 1098;

    extern const char*   SimpleMIDI_mid;
    const int            SimpleMIDI_midSize = 123;

    extern const char*   twoTrackScale_mid;
    const int            twoTrackScale_midSize = 277;

    extern const char*   tmpIcon_png;
    const int            tmpIcon_pngSize = 11067;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 4;

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
