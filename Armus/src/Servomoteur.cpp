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
	if(servo == SERVO_325)
		setAngleServo325(angle);
	else if(servo == SERVO_605)
		setAngleServo605(angle);
	else
		LCD_Printf("setAngleAjuste(int servo, int angle): servo invalide");
}

int choixMenu(int servomoteur)
{
	SERVO_Enable(servomoteur);
	setAngleAjuste(servomoteur, 0);

	int choix = 1;

	LCD_Printf("1: %i: CHOIX #%d\n",servomoteur, choix);
	while(true)
	{
		while(ANALOG_Read(BOUTON_CHOIX) == 0 && ANALOG_Read(BOUTON_VALIDER) == 0)
		{
			THREAD_MSleep(50);
		}

		if(ANALOG_Read(BOUTON_CHOIX) != 0) // Si on appuie sur le bouton choix
		{
			if(choix >= 4)	//angle > 180) // Si on est rendu au 4e choix et qu'on appuie encore, on retourne au choix #1
			{
				choix = 1;
			}
			else
			{
				++choix;
			}

			setAngleAjuste(servomoteur, (choix-1)*60);
			//setAngleAjuste(servomoteur, angle);
			THREAD_MSleep(500);

			LCD_Printf("1: %i: CHOIX #%d\n",servomoteur, choix);
		}
		if(ANALOG_Read(BOUTON_VALIDER) != 0) // Si on appuie sur le bouton valider
		{
			LCD_Printf("Vous avez fait le Choix #%d\n", choix);
			break; // On valide le choix et on sort de la fonction
		}
	}

	SERVO_Disable(servomoteur);
	return choix;
}

