/*
 * Servomoteur.h
 *
 *  Created on: 2014-11-16
 *      Author: Maxime
 */

#ifndef SERVOMOTEUR_H_
#define SERVOMOTEUR_H_

//Trouver experimentalement
const int DEBUT_325 = (-43);
const int FIN_325 = (134);
const int DEBUT_605 = (-23);
const int FIN_605 = (143);


//Branchement du fil jaune du servomoteur
const int SERVO_325 = 9;	//Connecteur A26
const int SERVO_605 = 10;	//Connecteur A25

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
int choixMenu(int servomoteur)
{
	int angle = -43;
	int choix = 1;
	bool validation = true;

	SERVO_Enable(servomoteur);
	SERVO_SetAngle(servomoteur, angle);
	THREAD_MSleep(1000);
	LCD_Printf("CHOIX #%d\n", choix);
	while(validation)
	{
		while(ANALOG_Read(2) == 0 && ANALOG_Read(3) == 0)
			THREAD_MSleep(20);
		if(ANALOG_Read(2) != 0) // Si on appuie sur le bouton choix
		{
			angle = angle + 60; //Le servo tourne de 60° pour montrer le choix suivant
			if(angle > 137) // Si on est rendu au 4e choix et qu'on appuie encore, on retourne au choix #1
			{
				angle = -43;
				SERVO_SetAngle(servomoteur, angle);
				THREAD_MSleep(500);
				choix = 1;
			}
			else
			{
				SERVO_SetAngle(servomoteur, angle);
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


#endif /* SERVOMOTEUR_H_ */
