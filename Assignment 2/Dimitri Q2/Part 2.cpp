
#include <iostream>
#include <fstream>
// For Sleep and GetAsyncKeyState
#include <Windows.h>

// For PlaySound
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")  // Link the winmm library
using namespace std;




class Audio {
    
public:
    char* p_buffer; 
    int N_buffer;   
    char* p_data;
    int N_data;
    short int NumChannels;
    int SampleRate;

    Audio(const char* file_name);
    ~Audio();
    void play();
};




int main()
{

    Audio Beam("beam_canonical.wav");

    cout << "\nThe number of channels is " << Beam.NumChannels;
    cout << "\nThe sample rate is " << Beam.SampleRate;

    Beam.play();


    cout << "\n\ndone.\n";
    return 0;
}


Audio::Audio(const char* file_name) {
    ifstream fin;


                                                // Open the binary file
    fin.open(file_name, ios::binary);
    if (!fin) {									// error check fin
        cout << "\nFile opening error.";
        return;
    }

                                                // Determine file size for buffer allocation
    fin.seekg(0, ios::end);                     // Move to end of file
    N_buffer = fin.tellg();                     // Get file size (position at end)
    fin.seekg(0, ios::beg);                     // Move back to start of file

    p_buffer = new char[N_buffer];              //dynamically allocated memory large enough to hold audio file
    if (p_buffer == nullptr) {
        cout << "\nDynamic memory allocation error";
        fin.close();
        return;
    }

    fin.read(p_buffer, N_buffer);
    fin.close();

    p_data = p_buffer + 44;
    N_data = N_buffer - 44;

 
    
    NumChannels = *(short int*)(p_buffer + 22);
    SampleRate = *(int*)(p_buffer + 24);


}

Audio::~Audio() {
    delete[] p_buffer;
    p_buffer = nullptr;
    p_data = nullptr;
}

void Audio::play() {
    PlaySoundA(p_buffer, NULL, SND_MEMORY | SND_SYNC);
    Sleep(1000);
}