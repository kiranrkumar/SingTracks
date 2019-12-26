# SingTracks

[In Progress] The goal of SingTracks is to create individual audio "practice" tracks from a MIDI file of an a cappella arrangement. Each audio track will have a different volume and left/right panning setting for each of the following groups of tracks/vocal parts as specified by the user:

- One particular vocal part (e.g. Alto 1)
- Solo & harmony parts
- Remaining background parts

For example, if a user has to learn her Alto 1 part for an arrangement, this app allows her to create a practice track from a MIDI file that has the Alto 1 part panned all the way left at a high volume, the solo and harmony parts panned center with a moderate volume, and the remaining background parts panned all the way right at a low volume. This way, the user can hear her part in the context of the full arrangement and, if listening on earbuds, remove the right ear bud to hear only her part and the solos if desired

Dec 26, 2019

The app is still in its early stages, but the highlights of what has been done are as follows:

- MIDI file selection
- Render MIDI file into a single, gain normalized audio track
- Sine wave synthesizers to produce the audio

The biggest remaining tasks are:

- Create multiple tracks
- Allow volume and panning adjustments for each group of tracks
- Enable custom name for each track
- Indicate which tracks are solo/harmony (vs background
