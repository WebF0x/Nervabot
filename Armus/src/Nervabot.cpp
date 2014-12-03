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

	/*while(true)
	{
		LCD_Printf("%d\n", choixMenu(SERVO_605));
		THREAD_MSleep(500);
		LCD_Printf("%d\n", choixMenu(SERVO_325));
		THREAD_MSleep(500);
	}

	THREAD_MSleep(5000);
	return 0;*/

	robot.initJeu();
	robot.jeuRecette();

	return 0;
}
