/*
============================================================================
 Name : Nervabot.cpp
 Author :
 Version :
 Description : Programme principal pour la qualification de la Grande Course
============================================================================
*/

#include "Robot.h"

int main()
{
	Robot robot;
	robot.calibrateWheels(10000);

	THREAD_MSleep(10000);

	robot.avancer(50);

	THREAD_MSleep(10000);

	robot.stop();

	return 0;
}
