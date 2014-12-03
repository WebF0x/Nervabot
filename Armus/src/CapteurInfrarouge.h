/*
 * CapteurInfrarouge.h
 *
 *  Created on: 2014-11-30
 *      Author: ngut2110
 */

#ifndef CAPTEURINFRAROUGE_H_
#define CAPTEURINFRAROUGE_H_


#include <libarmus.h>


const int CAPTEUR_GAUCHE 	= 1;
const int CAPTEUR_DROIT 	= 2;

bool capteurInfrarouge(int entree,int distance);
bool capteurAttendreDebut();


#endif /* CAPTEURINFRAROUGE_H_ */
