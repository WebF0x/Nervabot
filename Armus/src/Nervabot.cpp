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

	LCD_Printf("Calibrage\n");
	THREAD_MSleep(2000);
	robot.calibrateWheels(5000);

	LCD_Printf("Place moi sur ligne de depart\n");
	THREAD_MSleep(10000);

	robot.avancer(222, 50);
	THREAD_MSleep(1000);
	robot.tourner(90, 50);

	robot.avancer(50, 50);
	THREAD_MSleep(1000);
	robot.tourner(-90, 50);

	robot.avancer(45, 50);
	THREAD_MSleep(1000);
	robot.tourner(-90, 50);

	robot.avancer(50, 50);
	THREAD_MSleep(1000);
	robot.tourner(90, 50);

	robot.avancer(31, 50);
	THREAD_MSleep(1000);
	robot.tourner(-45, 50);

	robot.avancer(56, 50);
	THREAD_MSleep(1000);
	robot.tourner(90, 50);

	robot.avancer(82, 50);
	THREAD_MSleep(1000);
	robot.tourner(-45, 50);

	robot.avancer(50, 50);
	THREAD_MSleep(1000);
	robot.tourner(-12.5, 50);

	robot.avancer(100, 50);

	THREAD_MSleep(3000);
	robot.tourner(360, 50);
	robot.tourner(-360, 50);
	robot.tourner(1080, 50);

	return 0;
}
