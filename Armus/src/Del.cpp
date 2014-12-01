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
void del(int sortie, int fois, float temps)
{

	for(int i=0; i< fois; i++)
	{
		DIGITALIO_Write(sortie,1);//sorties 9 a 16
		THREAD_MSleep(temps);

		DIGITALIO_Write(sortie,0);
		THREAD_MSleep(temps);
	}
}
