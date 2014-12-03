/*
 * Del.h
 *
 *  Created on: 2014-11-30
 *      Author: ngut2110
 */

#ifndef DEL_H_
#define DEL_H_

#include <libarmus.h>

const int LAMBDA 	= 500;
const int DEL_O 	= 10; //connecteur D10
const int DEL_X 	= 9;  //connecteur D9

void delFlash(int delId, int duree);
void delOpen(int sortie);
void delClose(int sortie);

#endif /* DEL_H_ */
