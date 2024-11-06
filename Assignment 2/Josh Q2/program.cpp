// Assignment 4 Question #2
#include <iostream>
#include <cstdio>
#include <cmath>
#include <fstream>

#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")

#include "2D_graphics.h"
#include "timer.h"

using namespace std;

// 1) creating a class that stores relevant audio data and functions to obtain them
class Audio {

private:

public:
	char* p_buffer; // a dynamic memory buffer of N_buffer bytes that stores the binary file
	int N_buffer; // the number of bytes for the memory buffer

	char* p_data; // a pointer to the audio data in p_buffer
	int N_data; // the number of bytes for the audio data

	short int NumChannels; // the number of audio channels (1 - mono, 2 - stereo), 2 byte int
	int SampleRate; // the number of samples per second for the audio data (Hz), 4 byte int

	Audio(char* file_name);
	void play(); // use the Windows PlaySoundA function to play the wave file in p_buffer
	~Audio();

};

// 2) main function that demonstrates creating an Audio class instance and plays that instance
int main()
{
	Audio beam_canonical("beam_canonical.wav");

	cout << "\nNumber of channels: " << beam_canonical.NumChannels;
	cout << "\nSample rate: " << beam_canonical.SampleRate;

	beam_canonical.play();

	cout << "\ndone.\n";
	getchar();

	return 0;
}

// 1) constructor for Audio, reads all data from file, pulls out 
// the number of channels and sample rate
Audio::Audio(char* file_name) {
	
	ifstream fin;
	fin.open(file_name,ios::binary);

	if (!fin) {
		cout << "\nError opening file";
		return;
	}
	
	// finding length of file for dynamic memory allocation, the creating dynamic array
	fin.seekg(0, ios::end);
	N_buffer = fin.tellg();
	p_buffer = new char[N_buffer];
	//cout << "\nLength of file:" << N_buffer;

	if (p_buffer == NULL) {
		cout << "\nDynamic memory allocation error!";
		return;
	}

	fin.seekg(0, ios::beg);
	
	// reading file to created memory buffer
	fin.read(p_buffer, N_buffer);
	fin.close();

	// isolating data from the RIFF, fmt and first 8 bytes of the data sub-chunk
	N_data = N_buffer - 44;
	//cout << N_data;
	p_data = new char[N_data];
	p_data = (char*)(p_buffer + 44);

	// setting number of channels from memory buffer
	NumChannels = *(short int*)(p_buffer + 22);
	
	// setting sample rate from memory buffer
	SampleRate = *(int*)(p_buffer + 24);

	cout << "\nConstructor done constructing";
};

// 1) play function that plays from a memory buffer
void Audio::play(){
	// playing audio from memory buffer
	PlaySound(p_buffer, NULL, SND_MEMORY | SND_SYNC);
	Sleep(200);
};

// 1) deconstructor for Audio class
Audio::~Audio() {
	delete p_buffer;
	// p_data is not the original pointer/points to an overlapping buffer 
	// and thus does not need deleting (results in runtime error)
	//delete p_data;

	cout << "\nDestructor done destructing";
};
