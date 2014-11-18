/*
============================================================================
 Name : Armus.cpp
 Author : Equipe P4
 Description : Programme principal Nervabot
============================================================================
*/

#include "Robot.h"
#include "Servomoteur.h"

using namespace std;

//void* attendreSignal(void* arg);

int main()
{
	Robot robot(true);
	/*robot.inputInitialConditions();
	robot.trouverCible();*/
	choixMenu(SERVO_325);
	choixMenu(SERVO_605);
	THREAD_MSleep(5000);
	robot.tournerSurPlace(180);
	robot.stop();
	robot.avancer(100);
	robot.stop();
	THREAD_MSleep(5000);
	robot.tournerSurPlace(180);
	robot.stop();
	robot.avancer(100);
	robot.stop();
/*
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

//*/

	return 0;

}

/*void* attendreSignal(void* arg)
{
	Robot* r;
	r = (Robot*) arg;

	r->ecouterBruitFin();
	LCD_Printf("******* Son entendu *******\n");
}*/
