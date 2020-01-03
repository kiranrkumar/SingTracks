# SingTracks

The goal of SingTracks is to create individual audio practice tracks from a MIDI file of an a cappella arrangement. Each audio track will have  different volume and stereo panning setting for each of the following groups of vocal parts as specified by the user:

• One particular vocal part (e.g. Alto 1), called the "Primary" part
• Solo & harmony parts
• Remaining background parts

Consider the case where a user sings Alto for a song with a dedicated solo and four SATB (Soprano/Alto/Tenor/Bass) background parts. This singer could do the following with the app:

• Import the arrangement MIDI file 
• Pan the background parts all the way right and lower the volume by 12 dB
• Keep the solo panned center and lower the volume by 9 dB
• Pan the primary part all the way left and lower the volume by 3 dB

From this, four audio tracks will be created, each with different volume and panning characteristics:
• S: -3dB/panned left  ATB: -12dB/panned right  Solo: -9dB
• A: -3dB/panned left  STB: -12dB/panned right  Solo: -9dB
• T: -3dB/panned left  SAB: -12dB/panned right  Solo: -9dB
• B: -3dB/panned left  SAT: -12dB/panned right  Solo: -9dB

Thus, with one group of settings, each background singer has an audio track that isolates their part without losing the context of the rest of the song.

Jan 3, 2020

As of now, the app is in a minimal working state. Users can import a MIDI file, indicate which tracks are solos, and set volume and panning values for the following groups of tracks:
• Solo/Harmony
• Background
• Primary

Creating tracks from settings for the above groups will create as many audio files as there are background tracks (i.e. tracks that aren't marked as solo). Each track will have a different background track adhering to the primary group settings, while the remaining non-solo tracks following the background group settings.

This still needs many fixes and refinements, not the least of which include:
• Allowing the user to choose an output directory
• Having output file names adhere to the user-entered track names
• Adding a back button to easily go back and switching MIDI files without having to restart the app
• Adding better synth sounds (who wants to practice by listening to sine waves?)
