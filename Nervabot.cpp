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

int main()
{
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
		LCD_Printf("Lecture: %d - %d \n", lectureGauche, lectur	eDroit);

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
