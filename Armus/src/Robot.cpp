/*
 * Robot.cpp
 *
 *  Created on: 2014-10-01
 *  Author: Equipe P4
 */

#include "Robot.h"

Robot::Robot() : m_leftWheelSlope(1), m_rightWheelSlope(1), m_leftWheelOffset(0), m_rightWheelOffset(0)
{}

void Robot::stop()
{
	MOTOR_SetSpeed(MOTOR_LEFT, 0);
	MOTOR_SetSpeed(MOTOR_RIGHT, 0);
}

void Robot::avancer(float distance)
{
		int nbTarget = (float)distance/(WHEEL_DIAMETER*PI) * WHEEL_NB_COCHES;;

		int nbLeftTotal = 0;
		int nbRightTotal = 0;
		double nbLeft = 0 ;
		double nbRight = 0;

		int speedLeft = SPEEDTARGET;
		int speedRight = SPEEDTARGET;

		ENCODER_Read(ENCODER_LEFT);
		ENCODER_Read(ENCODER_RIGHT);
		while(nbLeftTotal < nbTarget || nbRightTotal < nbTarget)
		{
			if(nbLeftTotal < nbRightTotal)
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
			 MOTOR_SetSpeed(MOTOR_RIGHT, 0);
			}
			else if(nbLeftTotal > nbRightTotal)
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, 0);
			 MOTOR_SetSpeed(MOTOR_RIGHT, speedRight);
			}
			else
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
			 MOTOR_SetSpeed(MOTOR_RIGHT, speedRight);
			}
			nbLeft = ENCODER_Read(ENCODER_LEFT);
			nbRight = ENCODER_Read(ENCODER_RIGHT);

			nbLeftTotal += nbLeft;
			nbRightTotal+= nbRight;
		}
}

void Robot::tourner(float angle)
{
	int nbTotal = 0;

	int nbTarget = (float)DISTANCE_ROUES*fabs(angle)/360/(WHEEL_DIAMETER) * WHEEL_NB_COCHES;

	if(angle < 0.f)
		{
			MOTOR_SetSpeed(MOTOR_LEFT, SPEEDTARGET);
			MOTOR_SetSpeed(MOTOR_RIGHT, 0);
			ENCODER_Read(ENCODER_LEFT);
			while(nbTotal < nbTarget*2)
			{
				nbTotal += ENCODER_Read(ENCODER_LEFT);
			}
		}
		else
		{
			MOTOR_SetSpeed(MOTOR_RIGHT, SPEEDTARGET);
			MOTOR_SetSpeed(MOTOR_LEFT, 0);
			ENCODER_Read(ENCODER_RIGHT);
			while(nbTotal < nbTarget*2)
			{
				nbTotal += ENCODER_Read(ENCODER_RIGHT);
			}
		}
}

void Robot::writeInFile(const char* filename, const char* text)
{
	FILE *f = fopen(filename, "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	fprintf(f, text);

	fclose(f);
}

int Robot::lecture_couleur()
{
	return 0;
}

void Robot::endGame()
{
	const int BLANC = 3;
	const int JAUNE = 2;
	const int VERT = 1;
	const int BLEU = 0;
	int couleur_present = JAUNE;
	int x = 60;
	int corde = 0;
	int nb_Coche = 0;
	int rayon = 75;
	while(lecture_couleur() == couleur_present)
	{
		Deplacement d = avancerPrudemment(x);
		corde = d.distance;
		switch(d.raison)
		{
		case Raison::PireCouleur:
			int n = 0;
			tourner(180);
			avancer(corde/2);
			tourner(90); //Le sens va dépendre de la position du robot (GPS)
			avancerPrudemment(sqrt(rayon*rayon - corde * corde / 4));
			int D1 = d.distance;
			while(d.raison==Raison::Bumper && n < 6)
			{
				n++;
				tourner(90); // Le sens va dependre de la position
				Deplacement dist = suivreArc(sqrt(rayon*rayon - corde * corde / 4)-D1, true, 60);
				tourner(-90);
				avancerPrudemment(sqrt(rayon*rayon - corde * corde / 4)-D1);
				D1 = d.distance + D1;
			}
			break;
		case Raison::DistanceParcourue:
			bool versDroite = true;	//Guesser avec le gps
			Deplacement dist = suivreArc(x, versDroite, 2*PI*x);
			avancerPrudemment(40);
			if(d.raison==Raison::MeilleureCouleur)
			{
				couleur_present = BLEU;
				avancer(15);
			}
			break;
		case Raison::MeilleureCouleur:
			couleur_present = VERT;
			x = 30;
			rayon = 50;
			break;
		case Raison::Bumper:
			//Decider qu'est-ce qu'on fait en cas de contact
			break;
		}

	}

}

Robot::Deplacement Robot::avancerPrudemment(float distance)
{
		int nbTarget = (float)distance/(WHEEL_DIAMETER*PI) * WHEEL_NB_COCHES;;

		int nbLeftTotal = 0;
		int nbRightTotal = 0;
		double nbLeft = 0 ;
		double nbRight = 0;

		int speedLeft = SPEEDTARGETPRUDENT;
		int speedRight = SPEEDTARGETPRUDENT;

		int startColor = lecture_couleur();
		int currentColor = startColor;

		Deplacement resultat;
		resultat.raison = Raison::DistanceParcourue;

		ENCODER_Read(ENCODER_LEFT);
		ENCODER_Read(ENCODER_RIGHT);
		while(nbLeftTotal < nbTarget || nbRightTotal < nbTarget)
		{

			if(currentColor < startColor)
			{
				resultat.raison = Raison::MeilleureCouleur;
				break;
			}
			else if(currentColor > startColor)
			{
				resultat.raison = Raison::PireCouleur;
				break;
			}

			if(DIGITALIO_Read(BMP_FRONT))
			{
				resultat.raison = Raison::Bumper;
				break;
			}

			if(nbLeftTotal < nbRightTotal)
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
			 MOTOR_SetSpeed(MOTOR_RIGHT, 0);
			}
			else if(nbLeftTotal > nbRightTotal)
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, 0);
			 MOTOR_SetSpeed(MOTOR_RIGHT, speedRight);
			}
			else
			{
			 MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
			 MOTOR_SetSpeed(MOTOR_RIGHT, speedRight);
			}
			nbLeft = ENCODER_Read(ENCODER_LEFT);
			nbRight = ENCODER_Read(ENCODER_RIGHT);

			nbLeftTotal += nbLeft;
			nbRightTotal+= nbRight;
		}

		resultat.distance = nbLeftTotal*PI*WHEEL_DIAMETER/WHEEL_NB_COCHES;
		stop();
}


