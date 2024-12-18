#ifndef AUDIO_H
#define AUDIO_H

#include <Windows.h>  // Required for PlaySound
#include <MMSystem.h> // Required for PlaySound
#pragma comment(lib, "winmm.lib") // Link the winmm library
#include <string>

using namespace std;

class Audio {
public:
    // Constructor: Accepts 4 sound file paths
    Audio(const char* file1, const char* file2, const char* file3, const char* file4);
    ~Audio();

    // Play the next sound in the cycle
    void playNext();

private:
    const char* sounds[4]; // Array to store the file paths of the 4 sounds
    int currentSoundIndex; // Tracks which sound to play next
};

#endif // AUDIO_H