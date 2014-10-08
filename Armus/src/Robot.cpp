/*
 * Robot.cpp
 *
 *  Created on: 2014-10-01
 *      Author: dupm2216
 */

#include "Robot.h"

Robot::Robot() : m_leftWheelSlope(1), m_rightWheelSlope(1), m_leftWheelOffset(0), m_rightWheelOffset(0)
{
	// TODO Auto-generated constructor stub

}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}



void Robot::stop()
{
	MOTOR_SetSpeed(MOTOR_LEFT, 0);
	MOTOR_SetSpeed(MOTOR_RIGHT, 0);
}

void Robot::avancer(float distance)
{
	 int WAITTIME = 250;
	 const double K = 15;
	 int nbTarget = (float)distance/(WHEEL_DIAMETER*PI) * WHEEL_NB_COCHES;;
	 double nbLeft = 0 ;
	 int nbLeftTotal = 0;
	 double nbRight = 0;

	 int speedLeft = SPEEDTARGET;
	 int speedRight = SPEEDTARGET;

	 double error = 1;

	 ENCODER_Read(ENCODER_LEFT);
	 ENCODER_Read(ENCODER_RIGHT);
	 while(nbLeftTotal < nbTarget)
	 {

	 	MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
	 	MOTOR_SetSpeed(MOTOR_RIGHT, speedRight);

	 	THREAD_MSleep(WAITTIME);
	 	nbLeft = ENCODER_Read(ENCODER_LEFT);
	 	nbRight = ENCODER_Read(ENCODER_RIGHT);

	 	nbLeftTotal += nbLeft;
	 	error = nbLeft / nbRight;

	 	speedLeft = speedLeft - floor(((error-1)*K) + 0.5) ;
	 }
}


void Robot::tourner(float angle)
{
		 int nbTotal = 0;
		 int WAITTIME = 10;

	int nbTarget = (float)DISTANCE_ROUES*fabs(angle)/360/(WHEEL_DIAMETER) * WHEEL_NB_COCHES;

	if(angle < 0.f)
		{
			MOTOR_SetSpeed(MOTOR_LEFT, SPEEDTARGET);
			MOTOR_SetSpeed(MOTOR_RIGHT, 0);
			ENCODER_Read(ENCODER_LEFT);
			while(nbTotal < nbTarget*2)
			{
				//THREAD_MSleep(WAITTIME);
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
				//THREAD_MSleep(WAITTIME);
				nbTotal += ENCODER_Read(ENCODER_RIGHT);
			}
		}
}

void Robot::qualification()
{
		LCD_Printf("Place moi sur ligne de depart\n");

		THREAD_MSleep(1000);

		avancer(210);
		tourner(90);

		avancer(40);
		tourner(-90);

		avancer(30);
		tourner(-90);

		avancer(30);
		tourner(90);

		avancer(20);
		tourner(-45);

		avancer(30);
		tourner(90);

		avancer(55);
		tourner(-45);

		avancer(40);
		tourner(-12.5);

		avancer(50);

		/*THREAD_MSleep(3000);
		tourner(360);
		tourner(-360);
		tourner(1080);*/
}
