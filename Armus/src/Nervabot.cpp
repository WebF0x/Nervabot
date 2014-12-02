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
	Robot robot;
	AUDIO_SetVolume(100);

	robot.initJeu();
	robot.jeuRecette();

	return 0;
}
