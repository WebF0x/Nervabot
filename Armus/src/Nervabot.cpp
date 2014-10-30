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
	Robot robot;
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






/// Code de David pour threads et bumpers:
/*
typedef char* Robot_event_t;

void bumper_watch(Robot_event_t R_Event);
void robot_move();

enum
{
	BUMPER_FRONT_PUSHED = 1,
	BUMPER_REAR_PUSHED = 2,
	BUMPER_LEFT_PUSHED = 3,
	BUMPER_RIGHT_PUSHED = 4,
};


int main()
{
	THREAD thread_bumpers;
	THREAD thread_robot;
	Robot_event_t RobotEvent;

	LCD_ClearAndPrint("Demarage\n");
	thread_robot = THREAD_CreateSimple(robot_move);
	thread_robot = THREAD_CreateSimple(robot_move);

	for(bool fin = false;;)
	{
		if (RobotEvent != 0)
		{

		}
	}

	THREAD_Destroy(&thread_bumpers);
	THREAD_Destroy(&thread_robot);
	return 0;
}


void bumper_watch(Robot_event_t R_Event)
{

	while(1)
	{
		if(DIGITALIO_Read(BMP_FRONT))
		{
			LCD_Printf("Bumper front enfonce\n");
			//R_Event = BUMPER_FRONT_PUSHED;
		}
		else if(DIGITALIO_Read(BMP_REAR))
		{
			LCD_Printf("Bumper rear enfonce\n");
		}
		else if(DIGITALIO_Read(BMP_LEFT))
		{
			LCD_Printf("Bumper left enfonce\n");
		}
		else if(DIGITALIO_Read(BMP_RIGHT))
		{
			LCD_Printf("Bumper right enfonce\n");
		}


		THREAD_MSleep(100);
	}
}

//*/
