/*
 * Servomoteur.h
 *
 *  Created on: 2014-11-16
 *      Author: Maxime
 */

#ifndef SERVOMOTEUR_H_
#define SERVOMOTEUR_H_

#include <libarmus.h>

//Trouver experimentalement
const int DEBUT_325 = (-43);//Tested for 180 degrees
const int FIN_325 = (110);	//Tested for 180 degrees
const int DEBUT_605 = (-5);	//Tested for 180 degrees
const int FIN_605 = (135);	//Tested for 180 degrees


//Branchement du fil jaune du servomoteur
const int SERVO_325 = 9;	//Connecteur A26
const int SERVO_605 = 10;	//Connecteur A25

void setAngleServo325(int angle);
void setAngleServo605(int angle);
void setAngleAjuste(int servo, int angle);
int choixMenu(int servomoteur);

#endif /* SERVOMOTEUR_H_ */
