#pragma once

// used for the 
class BackgroundSound
{
public:
	//Constructor
	BackgroundSound();
	~BackgroundSound();

	//Methods
	void OpenSounds(const char* filename);
	void PlaySounds(void);
	void CloseSounds();

	//Public Variables
	const char* file;
	bool play = false;
};
