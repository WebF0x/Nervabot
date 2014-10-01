/*
============================================================================
 Name : Nervabot.cpp
 Author :
 Version :
 Description : Hello world - Exe source file
============================================================================
*/

// Include Files

#include <libarmus.h>

// Global Functions

void calibrateWheels()
{

	/*
	 * Three kinds of speed
	 * targetSpeed: What we tell the robot we want
	 * inputSpeed:	What the robot tells the motors
	 * realSpeed: 	What the motors gives us (we want this to be equal to targetSpeed)
	 *
	 * We want to find "a" and "b" in this equation:
	 * inputSpeed(targetSpeed) = a*targetSpeed + b
	 */

	///Take measurements #0
	int targetSpeed0 = 50;

	int inputSpeedLeft0 = targetSpeed0;
	int inputSpeedRight0 = targetSpeed0;

	MOTOR_SetSpeed(MOTOR_LEFT, inputSpeedLeft0);
	MOTOR_SetSpeed(MOTOR_RIGHT, inputSpeedRight0);

	THREAD_MSleep(1000);	//Some time to reach a stable speed

	//Reset counters
	ENCODER_Read(ENCODER_LEFT);
	ENCODER_Read(ENCODER_RIGHT);

	//Measure real speeds
	THREAD_MSleep(1000);
	int realSpeedLeft0 	= ENCODER_Read(ENCODER_LEFT);
	int realSpeedRight0 = ENCODER_Read(ENCODER_RIGHT);

	///Take measurements #1
	int targetSpeed1 = 100;

	int inputSpeedLeft1 = targetSpeed1;
	int inputSpeedRight1 = targetSpeed1;

	MOTOR_SetSpeed(MOTOR_LEFT, inputSpeedLeft1);
	MOTOR_SetSpeed(MOTOR_RIGHT, inputSpeedRight1);

	THREAD_MSleep(1000);	//Some time to reach a stable speed

	//Reset counters
	ENCODER_Read(ENCODER_LEFT);
	ENCODER_Read(ENCODER_RIGHT);

	//Measure real speeds
	THREAD_MSleep(1000);
	int realSpeedLeft1 	= ENCODER_Read(ENCODER_LEFT);
	int realSpeedRight1 = ENCODER_Read(ENCODER_RIGHT);

	///Find a (slope)
	float aLeft = (float)(inputSpeedLeft0 - inputSpeedLeft1) / (realSpeedLeft0 - realSpeedLeft1);
	float aRight = (float)(inputSpeedRight0 - inputSpeedRight1) / (realSpeedRight0 - realSpeedRight1);

	///Find b (offset)
	float bLeft = (float)inputSpeedLeft1 - aLeft*realSpeedLeft1;
	float bRight = (float)inputSpeedRight1 - aLeft*realSpeedRight1;

	///Display for debugging
	LCD_Printf("Left: %f , %f", aLeft, bLeft);
	LCD_Printf("Right: %f , %f", aRight, bRight);

	///Test our new function for debugging
	int targetSpeed = 50;
	MOTOR_SetSpeed(MOTOR_LEFT, targetSpeed*aLeft + bLeft);
	MOTOR_SetSpeed(MOTOR_RIGHT, targetSpeed*aRight + bRight);
}

void dispSpeedDifferences()
{
	for(int speed=0; speed<=100;speed+=10)
	{
		MOTOR_SetSpeed(MOTOR_LEFT, speed);
		MOTOR_SetSpeed(MOTOR_RIGHT, speed);

		THREAD_MSleep(1000);	//Some time to reach a stable speed

		//Reset counters
		ENCODER_Read(ENCODER_LEFT);
		ENCODER_Read(ENCODER_RIGHT);

		THREAD_MSleep(1000);
		int realSpeedLeft 	= ENCODER_Read(ENCODER_LEFT);
		int realSpeedRight 	= ENCODER_Read(ENCODER_RIGHT);

		int diffLeft = realSpeedLeft - speed;
		int diffRight = realSpeedRight - speed;

		if(speed%20==0) LCD_Printf("\n");
		else LCD_Printf(" | ");
		LCD_Printf("%d: %d - %d", speed, diffLeft, diffRight);
	}

	MOTOR_SetSpeed(MOTOR_LEFT, 0);
	MOTOR_SetSpeed(MOTOR_RIGHT, 0);
}


int main()
{
	LCD_Printf("Calibrating");
	calibrateWheels();
	return 0;

	LCD_Printf("Debut du programme!\n");

	int speedG = 50;
	int speedD = 50;

	MOTOR_SetSpeed(MOTOR_LEFT, speedG);
	MOTOR_SetSpeed(MOTOR_RIGHT, speedD);

	float facteurG=0.5;
	float facteurD=0.55;

	while(true)
	{
		THREAD_MSleep(100);

		int lectureGauche = ENCODER_Read(ENCODER_LEFT);
		int lectureDroit = ENCODER_Read(ENCODER_RIGHT);
		LCD_Printf("Lecture: %d - %d \n", lectureGauche, lectureDroit);

		int deficitGauche = -(lectureGauche-speedG);
		int deficitDroit = -(lectureDroit-speedD);
		LCD_Printf("Difference: %d - %d \n\n", deficitGauche, deficitDroit);

		int correctionGauche=deficitGauche*facteurG;
		int correctionDroit=deficitDroit*facteurD;

		MOTOR_SetSpeed(MOTOR_LEFT, speedG + correctionGauche );
		MOTOR_SetSpeed(MOTOR_RIGHT, speedD + correctionDroit);

	}

	return 0;
}
