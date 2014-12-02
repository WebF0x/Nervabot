/*
 * Del.cpp
 *
 *  Created on: 2014-11-30
 *      Author: ngut2110
 */

#include "Del.h"

//sortie d9 a d16
//fois: nb de repetition
//temps: temps dintervalle en ms
/*void delOpen(int sortie, int fois, float temps)
{


	for(int i=0; i< fois; i++)
		{

		DIGITALIO_Write(sortie,1);//sorties 9 a 16
		THREAD_MSleep(temps);

		DIGITALIO_Write(sortie,0);
		THREAD_MSleep(temps);
		}


	DIGITALIO_Write(sortie,1);//sorties 9 a 16

}*/

void delFlash(int delId, int duree)
{
	int nbPeriode = duree/LAMBDA;

	for(int i = 0; i < nbPeriode; i++)
	{
		THREAD_MSleep(LAMBDA/2);
		delOpen(delId);
		THREAD_MSleep(LAMBDA/2);
		delClose(delId);
	}
}

void delOpen(int sortie)
{
	DIGITALIO_Write(sortie,1);//sorties 9 a 16

}
void delClose(int sortie)
{
	DIGITALIO_Write(sortie,0);
}
