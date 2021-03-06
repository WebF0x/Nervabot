/*
 * CapteurInfrarouge.cpp
 *
 *  Created on: 2014-11-30
 *      Author: ngut2110
 */

#include "CapteurInfrarouge.h"

//entree: D1 a D8

//distance
//20cm - 260
//30cm - 180
//40cm - 140
//50cm - 120
//60cm - 105

bool capteurAttendreDebut()
{
	bool capteur1ready = false;
	bool capteur2ready = false;

	LCD_Printf("Attente d'un nouveau joueur\n");

	while(capteur1ready == false && capteur2ready == false)
	{
		capteur1ready = capteurInfrarouge(CAPTEUR_GAUCHE,260);
		capteur2ready = capteurInfrarouge(CAPTEUR_DROIT,260);
		THREAD_MSleep(50);
	}

	return true;
}

bool capteurInfrarouge(int capteur, int distance)
{
	if (ANALOG_Read(capteur) > distance)
	{
		return true;
	}

	return false;
}

