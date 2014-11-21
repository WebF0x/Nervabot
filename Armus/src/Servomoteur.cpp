/*
 * Servomoteur.cpp
 *
 *  Created on: 2014-11-20
 *      Author: Maxime
 */

#include "Servomoteur.h"

void setAngleServo325(int angle)
{
	int adjustedAngle = angle * (FIN_325-DEBUT_325) / 180 + DEBUT_325;
	SERVO_SetAngle(SERVO_325,adjustedAngle);

}

void setAngleServo605(int angle)
{
	int adjustedAngle = angle * (FIN_605-DEBUT_605) / 180 + DEBUT_605;
	SERVO_SetAngle(SERVO_605,adjustedAngle);

}

void setAngleAjuste(int servo, int angle)
{
	if(servo == 9)
		setAngleServo325(angle);
	else if(servo == 10)
		setAngleServo605(angle);
}
int choixMenu(int servomoteur)
{
	int angle = 0;
	int choix = 1;
	bool validation = true;

	SERVO_Enable(servomoteur);
	setAngleAjuste(servomoteur, angle);
	THREAD_MSleep(1000);
	LCD_Printf("CHOIX #%d\n", choix);
	while(validation)
	{
		while(ANALOG_Read(2) == 0 && ANALOG_Read(3) == 0)
			THREAD_MSleep(20);
		if(ANALOG_Read(2) != 0) // Si on appuie sur le bouton choix
		{
			angle = angle + 60; //Le servo tourne de 60° pour montrer le choix suivant
			if(angle > 180) // Si on est rendu au 4e choix et qu'on appuie encore, on retourne au choix #1
			{
				angle = 0;
				setAngleAjuste(servomoteur, angle);
				THREAD_MSleep(500);
				choix = 1;
			}
			else
			{
				setAngleAjuste(servomoteur, angle);
				THREAD_MSleep(500);
				choix++;
			}
			LCD_Printf("CHOIX #%d\n", choix);
		}
		if(ANALOG_Read(3) != 0) // Si on appuie sur le bouton valider
		{
			validation = false; // On valide le choix et on sort de la fonction
			LCD_Printf("Vous avez fait le Choix #%d\n", choix);
		}
	}
	SERVO_Disable(servomoteur);
	return choix;
}

