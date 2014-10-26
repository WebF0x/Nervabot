/*
 * Robot.cpp
 *
 *  Created on: 2014-10-01
 *  Author: Equipe P4
 */

#include "Robot.h"

Robot::Robot() : m_leftWheelSlope(1), m_rightWheelSlope(1), m_leftWheelOffset(0), m_rightWheelOffset(0)
{}

Robot::~Robot()
{}

void Robot::stop()
{
	MOTOR_SetSpeed(MOTOR_LEFT, 0);
	MOTOR_SetSpeed(MOTOR_RIGHT, 0);
}

void Robot::avancer(float distance)
{
		int nbTarget = (float)distance/(WHEEL_DIAMETER*PI) * WHEEL_NB_COCHES;;

		int nbLeftTotal = 0;
		int nbRightTotal = 0;
		double nbLeft = 0 ;
		double nbRight = 0;

		int speedLeft = SPEEDTARGET;
		int speedRight = SPEEDTARGET;

		double error = 1;

		ENCODER_Read(ENCODER_LEFT);
		ENCODER_Read(ENCODER_RIGHT);
		while(nbLeftTotal < nbTarget)
		{
			if(nbLeftTotal < nbRightTotal)
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
			 MOTOR_SetSpeed(MOTOR_RIGHT, 0);
			}
			else if(nbLeftTotal > nbRightTotal)
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, 0);
			 MOTOR_SetSpeed(MOTOR_RIGHT, speedRight);
			}
			else
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
			 MOTOR_SetSpeed(MOTOR_RIGHT, speedRight);
			}
			nbLeft = ENCODER_Read(ENCODER_LEFT);
			nbRight = ENCODER_Read(ENCODER_RIGHT);

			nbLeftTotal += nbLeft;
			nbRightTotal+= nbRight;
		}
}

void Robot::avancer(float distance, int vitesse)
{
		int nbTarget = (float)distance/(WHEEL_DIAMETER*PI) * WHEEL_NB_COCHES;;

		int nbLeftTotal = 0;
		int nbRightTotal = 0;
		double nbLeft = 0 ;
		double nbRight = 0;

		int speedLeft = vitesse;
		int speedRight = vitesse;

		double error = 1;

		ENCODER_Read(ENCODER_LEFT);
		ENCODER_Read(ENCODER_RIGHT);
		while(nbLeftTotal < nbTarget)
		{
			if(nbLeftTotal < nbRightTotal)
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
			 MOTOR_SetSpeed(MOTOR_RIGHT, 0);
			}
			else if(nbLeftTotal > nbRightTotal)
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, 0);
			 MOTOR_SetSpeed(MOTOR_RIGHT, speedRight);
			}
			else
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
			 MOTOR_SetSpeed(MOTOR_RIGHT, speedRight);
			}
			nbLeft = ENCODER_Read(ENCODER_LEFT);
			nbRight = ENCODER_Read(ENCODER_RIGHT);

			nbLeftTotal += nbLeft;
			nbRightTotal+= nbRight;
		}
}

void Robot::tourner(float angle)
{
	int nbTotal = 0;

	int nbTarget = (float)DISTANCE_ROUES*fabs(angle)/360/(WHEEL_DIAMETER) * WHEEL_NB_COCHES;

	if(angle < 0.f)
		{
			MOTOR_SetSpeed(MOTOR_LEFT, SPEEDTARGET);
			MOTOR_SetSpeed(MOTOR_RIGHT, 0);
			ENCODER_Read(ENCODER_LEFT);
			while(nbTotal < nbTarget*2)
			{
				nbTotal += ENCODER_Read(ENCODER_LEFT);
			}
		}
		else
		{
			MOTOR_SetSpeed(MOTOR_RIGHT, SPEEDTARGET);
			MOTOR_SetSpeed(MOTOR_LEFT, 0);
			ENCODER_Read(ENCODER_RIGHT);
			while(nbTotal < nbTarget*2)
			{
				nbTotal += ENCODER_Read(ENCODER_RIGHT);
			}
		}
}

void Robot::qualification()
{
		LCD_Printf("Place moi sur ligne de depart\n");

		THREAD_MSleep(1000);

		avancer(215.5);
		tourner(90);

		avancer(36);
		tourner(-90);

		avancer(33);
		tourner(-90);

		avancer(34);
		tourner(90);

		avancer(23);
		tourner(-45);

		avancer(28);
		tourner(90);

		avancer(63);
		tourner(-45);

		avancer(40);
		tourner(-12.5);

		avancer(100);

		stop();
}

void Robot::writeInFile(const char* filename, const char* text)
{
	FILE *f = fopen(filename, "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	fprintf(f, text);

	fclose(f);
}




