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
const int SERVO_325 = 1;	//Connecteur A26
const int SERVO_605 = 2;	//Connecteur A25

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


#endif /* SERVOMOTEUR_H_ */
