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
	Robot robot(false);
	robot.inputInitialConditions();

	robot.trouverCible();

	return 0;
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
	THREAD_Create(&thread_bumpers, bumper_watch(RobotEvent), );
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
void robot_move()
{
	Robot robot;
	robot.avancer(10,50);
}
//*/
