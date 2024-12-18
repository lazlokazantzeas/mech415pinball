#include "Audio.h"

// Constructor: Initialize the array of sounds
Audio::Audio(const char* file1, const char* file2, const char* file3, const char* file4) {
    sounds[0] = file1;
    sounds[1] = file2;
    sounds[2] = file3;
    sounds[3] = file4;
    currentSoundIndex = 0;
}

// Destructor: Nothing to clean up for this implementation
Audio::~Audio() {}

// Play the next sound in the cycle
void Audio::playNext() {
    // Play the current sound
    PlaySoundA(sounds[currentSoundIndex], NULL, SND_FILENAME | SND_SYNC);

    // Move to the next sound (cycle back to the first after the fourth)
    currentSoundIndex = (currentSoundIndex + 1) % 4;
}
