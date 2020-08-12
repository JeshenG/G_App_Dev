#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "BackgroundSound.h"

using namespace std;

/**Constructor**/
BackgroundSound::BackgroundSound()
{
}

BackgroundSound::~BackgroundSound()
{
}

/**Methods**/
void BackgroundSound::OpenSounds(const char* filename)
{
	CloseSounds();
	char result[100];
	file = filename;
	strcpy_s(result, "open ");
	strcat_s(result, file);
	strcat_s(result, " type waveaudio alias sound");
	mciSendStringA(result, 0, 0, 0);
	play = true;
}

void BackgroundSound::PlaySounds(void)
{
	mciSendStringA("play sound", 0, 0, 0);

}

void BackgroundSound::CloseSounds(void)
{
	mciSendStringA("close sound", 0, 0, 0);
}
