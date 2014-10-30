/*
============================================================================
 Name : Armus.cpp
 Author : Equipe P4
 Description : Programme principal Nervabot
============================================================================
*/

#include "Robot.h"

void* attendreSignal(void* arg);

int main()
{
	Robot robot(true);
	THREAD bruitFin;
	bool isFirstRobot;

	isFirstRobot = robot.inputInitialConditions();
	LCD_Printf("Position choisie\n");
	LCD_Printf("En attente du signal de depart\n");
	robot.attendreBruitDepart();

	if(!isFirstRobot)
	{
		THREAD_MSleep(3000);
		robot.attendreBruitDepart();	//Attendre le deuxieme sifflet de depart
	}

	THREAD_Create(&bruitFin, attendreSignal, &robot);

	//Debut de la course
	robot.trouverCible();
	robot.endGame();

	THREAD_Destroy(&bruitFin);

	return 0;
}

void* attendreSignal(void* arg)
{
	Robot* r;
	r = (Robot*) arg;

	r->ecouterBruitFin();
	LCD_Printf("******* Son entendu *******\n");
}
