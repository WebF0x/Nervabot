/*
 * capteurCouleur.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: Jeremie
 */

#include "capteurCouleur.h"

int adjd_dev;


// fonctions globales


//permet de changer la valeur des registres
void adjd_SetRegister(unsigned char reg, unsigned char val)
{
	unsigned char data[2];
	data[0] = reg;
	data[1] = val;
	armus::i2c_Write(adjd_dev, 2, data);
}

//permet de changer la valeur des registres de 16 bits
void adjd_SetRegister16(unsigned char reg, int val)
{
	unsigned char data[2];
	data[0] = reg;
	data[1] = val & 0xFF;
	armus::i2c_Write(adjd_dev, 2, data);
	data[0] = reg+1;
	data[1] = (val >> 8) & 0xFF;
	armus::i2c_Write(adjd_dev, 2, data);
}

//permet de lire la valeur des registres
unsigned char adjd_ReadRegister(unsigned char reg)
{
	unsigned char val;

	armus::i2c_ReadAfterWrite(adjd_dev, 1, &reg, 1, &val);

	return val;
}

//permet de lire la valeur des registres de 16 bits
int adjd_ReadRegister16(unsigned char reg)
{
	int val16;
	unsigned char val;
	armus::i2c_ReadAfterWrite(adjd_dev, 1, &reg, 1, &val);
	val16 = val;
	reg = reg+1;
	armus::i2c_ReadAfterWrite(adjd_dev, 1, &reg, 1, &val);
	val16 = val16 + ((val << 8) & 0xFF00);
	return val16;
}


// Permet de connaitre la valeur du CAP dans le registre
// prend comme argument une constante CAP_RED, CAP_BLUE, CAP_CLEAR ou CAP_GREEN
// retourne un unsigned char de la valeur
unsigned char cap_GetValue(unsigned char cap_address)
{
	unsigned char cap_value;

	cap_value = adjd_ReadRegister(cap_address);

	return cap_value;
}


// Permet de changer la valeur du CAP dans le registre
// prend comme premier argument une constante CAP_RED, CAP_BLUE, CAP_CLEAR ou CAP_GREEN
// le second argument est compris entre 0 et 15, et determine la valeur du cap a ecrire dans le registre
void cap_SetValue(unsigned char cap_address, unsigned char cap_value)
{
	adjd_SetRegister(cap_address, cap_value);
}



// Permet de connaitre la valeur du CAP dans le registre
// address est une constante comme INTEGRATION_RED, ...
// retourne un int de la valeur
int integrationTime_GetValue(unsigned char address)
{
	int time_value;

	time_value = adjd_ReadRegister16(address);

	return time_value;
}


// Permet de changer la valeur du CAP dans le registre
// address est une constante comme INTEGRATION_RED, ...
// time_value est compris entre 0 et 4095
void integrationTime_SetValue(unsigned char address, int time_value)
{
	adjd_SetRegister16(address, time_value);
}


// Vous devez vous-meme modifier cette fonction tout dependamment de la sortie numerique utilisee
void led_TurnOff()
{
	// TODO : code a changer
	DIGITALIO_Write(9, 0);
}

// Vous devez vous-meme modifier cette fonction tout dependamment de la sortie numerique utilisee
void led_TurnOn()
{
	// TODO : code a changer
	DIGITALIO_Write(9, 1);
}

// permet de faire une lecture differentielle avec et sans eclairage de la led
void color_Read(int& data_red, int& data_blue, int& data_green, int& data_clear)
{
	//premiere lecture sans eclairage
	led_TurnOff();

	adjd_SetRegister(ADJD_REG_CONFIG, 1 << CONFIG_TOFS);
	adjd_SetRegister(ADJD_REG_CTRL, 1 << CTRL_GOFS);
	while(adjd_ReadRegister(ADJD_REG_CTRL))
	{
		THREAD_MSleep(50);
	}

	//lecture avec eclairage
	led_TurnOn();
	adjd_SetRegister(ADJD_REG_CTRL, 1 << CTRL_GSSR);
	while(adjd_ReadRegister(ADJD_REG_CTRL))
	{
		THREAD_MSleep(50);
	}

	//eteindre la led
	led_TurnOff();

	data_red = adjd_ReadRegister16(DATA_RED_LO);
	data_green = adjd_ReadRegister16(DATA_GREEN_LO);
	data_blue = adjd_ReadRegister16(DATA_BLUE_LO);
	data_clear = adjd_ReadRegister16(DATA_CLEAR_LO);
}

void color_ReadToCalibrate(int& data_red, int& data_blue, int& data_green, int& data_clear)
{
	led_TurnOn();
	adjd_SetRegister(ADJD_REG_CONFIG, 0 << CONFIG_TOFS);
	adjd_SetRegister(ADJD_REG_CTRL, 1 << CTRL_GSSR);
	while(adjd_ReadRegister(ADJD_REG_CTRL))
	{
		THREAD_MSleep(50);
	}
	led_TurnOff();

	data_red = adjd_ReadRegister16(DATA_RED_LO);
	data_green = adjd_ReadRegister16(DATA_GREEN_LO);
	data_blue = adjd_ReadRegister16(DATA_BLUE_LO);
	data_clear = adjd_ReadRegister16(DATA_CLEAR_LO);

}

// l argument est un integer qui ne doit pas etre modifie
int color_Init(int& dev_handle)
{
	int error;
	error = armus::i2c_RegisterDevice(ADJD_S371_QR999_SADR, 100000, 1000, dev_handle);

	return error;
}

float fmax(float a, float b, float c)
{
	a = (a<b)?b:a;
	return (a<c)?c:a;
}

float fmin(float a, float b, float c)
{
	a = (a>b)?b:a;
	return (a>c)?c:a;
}

float rgbToHue(float r, float b, float g)
{
    float rgb_max = fmax(r,g, b);
    float rgb_min = fmin(r, g, b);
    float delta = rgb_max - rgb_min;

    float hue;
    if (r == rgb_max)
        hue = (g - b) / (delta + 1e-20f);
    else if (g == rgb_max)
        hue = 2 + (b - r) / (delta + 1e-20f);
    else
        hue = 4 + (r - g) / (delta + 1e-20f);
    if (hue < 0)
        hue += 6.f;
    return hue * (1.f / 6.f);
}

float rgbToSaturation(float r, float b, float g)
{
    float rgb_max = fmax(r,g, b);
    float rgb_min = fmin(r, g, b);
    float delta = rgb_max - rgb_min;

    return delta / (rgb_max + 1e-20f);
}


float rgbToValue(float r, float b, float g)
{
    return fmax(r,g, b);
}

int getCurrentColorA()
{
	int r, b, g, clear;
	color_Read(r, b, g, clear);
	float hue = rgbToHue(r,b,g);
	float saturation = rgbToSaturation(r,b,g);
	float red = 0.02;
	float green = 0.46;
	float blue = 0.63;
	float yellow = 0.12;
	float inc = 0.045;
	int couleur;

	if(saturation < 0.3)
		couleur= 3;
	else if(hue > (red-inc) && hue < (red+inc)){
		couleur= 4;
	}
	else if(hue > (green-inc) && hue < (green+inc)){
		couleur= 1;
	}
	else if(hue > (blue-inc) && hue < (blue+inc)){
		couleur= 0;
	}
	else if(hue > (yellow-inc) && hue < (yellow+inc)){
		couleur= 2;
	}
	else
		couleur= 3;

	return couleur;
}

int getCurrentColorB()
{
	int r, b, g, clear;
	color_Read(r, b, g, clear);
	float hue = rgbToHue(r,b,g);
	float saturation = rgbToSaturation(r,b,g);
	float value = rgbToValue(r,b,g);
	float red = 0.995;
	float green = 0.5;
	float blue = 0.68;
	float yellow = 0.15;
	float inc = 0.07;
	int couleur;

	if(saturation < 0.1)
	{
		if(value < 160) couleur = 1;
		else couleur = 3;
	}
	else if((hue > 0.8 && hue > (red-inc)) || (hue < 0.2 && hue < (red-1+inc))){
		couleur = 4;
	}
	else if(hue > (blue-inc) && hue < (blue+inc)){
		couleur =  0;
	}
	else if(hue > (yellow-inc) && hue < (yellow+inc)){
		couleur =  2;
	}
	else{
		couleur =  3;
	}
	return couleur;
}

void showRGB()
{
	int r, b, g, clear;
	color_Read(r, b, g, clear);
	float hue = rgbToHue(r, b,g);
	float saturation = rgbToSaturation(r, b,g);
	float value = rgbToValue(r, b,g);
	LCD_ClearAndPrint("%i  %i %i \n %3f %3f %3f", r, b, g, hue, saturation, value);
}

void initA()
{
	//initialisation du capteur
	ERROR_CHECK(color_Init(adjd_dev));

	cap_SetValue(CAP_RED, 15);
	cap_SetValue(CAP_GREEN, 15);
	cap_SetValue(CAP_BLUE, 15);
	cap_SetValue(CAP_CLEAR, 15);

	integrationTime_SetValue(INTEGRATION_RED, 1120);
	integrationTime_SetValue(INTEGRATION_GREEN, 980);
	integrationTime_SetValue(INTEGRATION_BLUE, 1300);
	integrationTime_SetValue(INTEGRATION_CLEAR, 255);
}

void initB()
{
	//initialisation du capteur
	ERROR_CHECK(color_Init(adjd_dev));

	cap_SetValue(CAP_RED, 15);
	cap_SetValue(CAP_GREEN, 15);
	cap_SetValue(CAP_BLUE, 15);
	cap_SetValue(CAP_CLEAR, 15);

	integrationTime_SetValue(INTEGRATION_RED, 160);
	integrationTime_SetValue(INTEGRATION_GREEN, 165);
	integrationTime_SetValue(INTEGRATION_BLUE, 197);
	integrationTime_SetValue(INTEGRATION_CLEAR, 255);
}

