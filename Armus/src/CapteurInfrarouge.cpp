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

int capteurInfrarouge(int entree,int distance)
{
	//THREAD_MSleep(500);
	//while (ANALOG_Read(entree) < distance)
	//{
		//LCD_Printf("valeur: #%d", ANALOG_Read(entree));
		//LCD_Printf("loin");
		//THREAD_MSleep(1000);
	//}


	if (ANALOG_Read(entree) > distance)
	{
		//LCD_Printf("1");
		return 1;
	}

	return 0;
}

