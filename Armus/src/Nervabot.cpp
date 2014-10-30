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
	LCD_Printf("Position choisi\n");
	LCD_Printf("En attente du signal de depart\n");
	robot.attendreBruitDepart();

	if(!isFirstRobot)
	{
		THREAD_MSleep(3000);
		robot.attendreBruitDepart();	//Attendre le deuxieme sifflet de depart
	}

	THREAD_Create(&bruitFin, attendreSignal, &robot);
/*
	Robot::Deplacement d = robot.avancerPrudemment(100);
	switch(d.raison)
	{
		case Robot::DistanceParcourue:
		{
			LCD_Printf("DistanceParcourue");
			break;
		}
		case Robot::PireCouleur:
		{
			LCD_Printf("PireCouleur");
			break;
		}
		case Robot::MeilleureCouleur:
		{
			LCD_Printf("MeilleureCouleur");
			break;
		}
		case Robot::Bumper:
		{
			LCD_Printf("Bumper");
			break;
		}
	}
	return 0;
	//*/

	robot.inputInitialConditions();
	robot.trouverCible();

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
