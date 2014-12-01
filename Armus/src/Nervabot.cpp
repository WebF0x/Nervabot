/*
============================================================================
 Name : Armus.cpp
 Author : Equipe P4
 Description : Programme principal Nervabot
============================================================================
*/

#include "Robot.h"

using namespace std;

int main()
{
	Robot robot(true);
    Voice voice;
    voice.play(687);
	/*
	AUDIO_SetVolume(100);
	AUDIO_PlayFile("audio.wav");
	THREAD_MSleep(10000);
	*/

	//robot.jeuRecette();
	//choixMenu(SERVO_325);

	return 0;
}
