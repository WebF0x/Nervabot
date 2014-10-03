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

/**
	 * Three kinds of speed
	 * targetSpeed: What we tell the robot we want
	 * inputSpeed:	What the robot tells the motors
	 * realSpeed: 	What the motors gives us (we want this to be equal to targetSpeed)
	 *
	 * We want to find "wheelSlope" and "wheelOffset" in this equation:
	 * inputSpeed(targetSpeed) = wheelSlope*targetSpeed + wheelOffset
**/
void Robot::calibrateWheels(const int millis)
{
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
	THREAD_MSleep(millis);
	int realSpeedLeft0 	= ENCODER_Read(ENCODER_LEFT)*1000/millis;
	int realSpeedRight0 = ENCODER_Read(ENCODER_RIGHT)*1000/millis;

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
	THREAD_MSleep(millis);
	int realSpeedLeft1 	= ENCODER_Read(ENCODER_LEFT)*1000/millis;
	int realSpeedRight1 = ENCODER_Read(ENCODER_RIGHT)*1000/millis;

	///Find wheelSlope
	m_leftWheelSlope = (float)(inputSpeedLeft0 - inputSpeedLeft1) / (realSpeedLeft0 - realSpeedLeft1);
	m_rightWheelSlope = (float)(inputSpeedRight0 - inputSpeedRight1) / (realSpeedRight0 - realSpeedRight1);

	///Find wheelOffset
	m_leftWheelOffset = (float)inputSpeedLeft1 - m_leftWheelSlope*realSpeedLeft1;
	m_rightWheelOffset = (float)inputSpeedRight1 - m_rightWheelSlope*realSpeedRight1;

	///Stop
	MOTOR_SetSpeed(MOTOR_LEFT, 0);
	MOTOR_SetSpeed(MOTOR_RIGHT, 0);

}

void Robot::dispSpeedDifferences()
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

void Robot::avancer(int targetSpeed)
{
	int leftSpeed = m_leftWheelSlope * targetSpeed + m_leftWheelOffset;
	int rightSpeed = m_rightWheelSlope * targetSpeed + m_rightWheelOffset;

	MOTOR_SetSpeed(MOTOR_LEFT, leftSpeed);
	MOTOR_SetSpeed(MOTOR_RIGHT, rightSpeed);
}

void Robot::stop()
{
	MOTOR_SetSpeed(MOTOR_LEFT, 0);
	MOTOR_SetSpeed(MOTOR_RIGHT, 0);
}

void Robot::avancer(int distance, int vitesse)
{
	ENCODER_Read(ENCODER_LEFT);

	avancer(vitesse);

	int nbCocheTotal = (float)distance/(WHEEL_DIAMETER*PI) * WHEEL_NB_COCHES;

	int nbCoche = 0;

	while(nbCoche < nbCocheTotal)
	{
		THREAD_MSleep(100);
		nbCoche += ENCODER_Read(ENCODER_LEFT);
	}

	stop();
}

void Robot::tourner(float angle, int vitesse)
{
	stop();

	ENCODER_Read(ENCODER_LEFT);

	int nbCocheTotal = (float)DISTANCE_ROUES*fabs(angle)/360/(WHEEL_DIAMETER) * WHEEL_NB_COCHES;

	int nbCoche = 0;

	int leftSpeed = m_leftWheelSlope * vitesse + m_leftWheelOffset;
	int rightSpeed = m_rightWheelSlope * vitesse + m_rightWheelOffset;
	if(angle < 0.f)
	{
		rightSpeed *= -1;
	}
	else
	{
		leftSpeed *= -1;
	}
	MOTOR_SetSpeed(MOTOR_LEFT, leftSpeed);
	MOTOR_SetSpeed(MOTOR_RIGHT, rightSpeed);

	while(nbCoche < nbCocheTotal)
	{
		THREAD_MSleep(100);
		nbCoche += ENCODER_Read(ENCODER_LEFT);
	}

	stop();
}

void Robot::qualification()
{
	LCD_Printf("Calibrage\n");
		THREAD_MSleep(2000);
		calibrateWheels(5000);

		LCD_Printf("Place moi sur ligne de depart\n");
		THREAD_MSleep(10000);

		avancer(222, 50);
		THREAD_MSleep(1000);
		tourner(90, 50);

		avancer(50, 50);
		THREAD_MSleep(1000);
		tourner(-90, 50);

		avancer(45, 50);
		THREAD_MSleep(1000);
		tourner(-90, 50);

		avancer(50, 50);
		THREAD_MSleep(1000);
		tourner(90, 50);

		avancer(31, 50);
		THREAD_MSleep(1000);
		tourner(-45, 50);

		avancer(56, 50);
		THREAD_MSleep(1000);
		tourner(90, 50);

		avancer(82, 50);
		THREAD_MSleep(1000);
		tourner(-45, 50);

		avancer(50, 50);
		THREAD_MSleep(1000);
		tourner(-12.5, 50);

		avancer(100, 50);

		THREAD_MSleep(3000);
		tourner(360, 50);
		tourner(-360, 50);
		tourner(1080, 50);
}
