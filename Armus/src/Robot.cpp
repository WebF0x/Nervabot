/*
 * Robot.cpp
 *
 *  Created on: 2014-10-01
 *  Author: Equipe P4
 */

#include "Robot.h"

using namespace std;

Robot::Robot(bool isArmu022)
{
	if(isArmu022) initB();
	else initA();
}

void Robot::stop()
{
	MOTOR_SetSpeed(MOTOR_LEFT, 0);
	MOTOR_SetSpeed(MOTOR_RIGHT, 0);
}

/*
 * Si vous avez besoin de la position et l'orientation du robot, preferez la fonction avancerPrudemment()
 * Naif, assume qu'il n'y a aucune collision
 * Privilegier avancerPrudemment() pour la grande course
 */
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
		if (m_stopAll == false)
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
}

/*
 * Si vous avez besoin de la position et l'orientation du robot, preferez la fonction tournerSurPlace()
 */
void Robot::tourner(float angle)
{
	if (m_stopAll == false)
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
}

//Angle entre -180 et 180
void Robot::tournerSurPlace(float angle)
{
	if (m_stopAll == false)
	{
		float distance = (PI*DISTANCE_ROUES)*fabs(angle)/360;
		int nbTarget = distance * WHEEL_NB_COCHES/PI/WHEEL_DIAMETER;
	
		int leftSpeed = (angle > 0.f) ? -SPEEDTARGETPRUDENT : SPEEDTARGETPRUDENT;
		int rightSpeed = (angle > 0.f) ? SPEEDTARGETPRUDENT : -SPEEDTARGETPRUDENT;
	
		int nbLeftTotal = 0;
		int nbRightTotal = 0;
		ENCODER_Read(ENCODER_LEFT);
		ENCODER_Read(ENCODER_RIGHT);
	
		while(nbLeftTotal < nbTarget || nbRightTotal < nbTarget)
		{
			if(nbLeftTotal < nbRightTotal)
			{
				MOTOR_SetSpeed(MOTOR_LEFT, leftSpeed);
				MOTOR_SetSpeed(MOTOR_RIGHT, 0);
			}
			else if(nbLeftTotal > nbRightTotal)
			{
				MOTOR_SetSpeed(MOTOR_LEFT, 0);
				MOTOR_SetSpeed(MOTOR_RIGHT, rightSpeed);
			}
			else
			{
				MOTOR_SetSpeed(MOTOR_LEFT, leftSpeed);
				MOTOR_SetSpeed(MOTOR_RIGHT, rightSpeed);
			}
	
			nbLeftTotal += ENCODER_Read(ENCODER_LEFT);
			nbRightTotal+= ENCODER_Read(ENCODER_RIGHT);
		 }
	
			stop();
			setOrientation(m_orientation + angle);
	}
}

/*
 * Pas full utile pour la course mais je garde peut-etre pour plus tard
 */
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
	int r, b, g, clear;
	color_Read(r, b, g, clear);
	float hue = rgbToHue(r,b,g);
	float red = 0.03;
	float green = 0.44;
	float blue = 0.62;
	float yellow = 0.1;
	float inc = 0.04;

	if(hue > (red-inc) && hue < (red+inc))
		return ROUGE;
	else if(hue > (green-inc) && hue < (green+inc))
		return VERT;
	else if(hue > (blue-inc) && hue < (blue+inc))
		return BLEU;
	else if(hue > (yellow-inc) && hue < (yellow+inc))
		return JAUNE;
	else
		return BLANC;
}

int random(int low, int high)
{
	srand(time(NULL));
	return rand() % (high - low + 1) + low;
}

/*
Robot::Deplacement Robot::suivreArc(float rayon, bool versDroite, float distance)
{
	Deplacement resultat;
	resultat.raison = DistanceParcourue;

	float vraiRayonLeft = (versDroite) ? rayon + DISTANCE_ROUES/2 : rayon - DISTANCE_ROUES/2;
	float vraiRayonRight = (versDroite) ? rayon - DISTANCE_ROUES/2 : rayon + DISTANCE_ROUES/2;
	
	float rapport = vraiRayonLeft/vraiRayonRight;
	float portion = distance / (2*PI*rayon);
	float distanceLeft = 2*PI*vraiRayonLeft*portion;
	float distanceRight = 2*PI*vraiRayonRight*portion;
	int nbTargetLeft = distanceLeft / (WHEEL_DIAMETER*PI) * WHEEL_NB_COCHES;
	int nbTargetRight = distanceRight / (WHEEL_DIAMETER*PI) * WHEEL_NB_COCHES;
	int nbTotalRight = 0;
	int nbTotalLeft = 0;
	int nbLeft = 0;
	int nbRight = 0;

	int speedLeft = SPEEDTARGETPRUDENT;
	int speedRight = SPEEDTARGETPRUDENT*rapport;

	ENCODER_Read(ENCODER_LEFT);
	ENCODER_Read(ENCODER_RIGHT);
	while(nbTotalLeft < nbTargetLeft || nbTotalRight < nbTargetRight)
	{
		if(nbTotalLeft < rapport*nbTotalRight)
		{
			MOTOR_SetSpeed(MOTOR_LEFT, speedLeft);
			MOTOR_SetSpeed(MOTOR_RIGHT, 0);
		}
		else if(nbTotalLeft > rapport*nbTotalRight)
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

		nbTotalLeft += nbLeft;
		nbTotalRight += nbRight;
	}

	resultat.distance = (nbTotalLeft / WHEEL_NB_COCHES * (WHEEL_DIAMETER*PI))+(nbTotalRight / WHEEL_NB_COCHES * (WHEEL_DIAMETER*PI))/2;

	return resultat;
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
		resultat.raison = DistanceParcourue;

		ENCODER_Read(ENCODER_LEFT);
		ENCODER_Read(ENCODER_RIGHT);
		while(nbLeftTotal < nbTarget || nbRightTotal < nbTarget)
		{
			if(currentColor < startColor)
			{
				resultat.raison = MeilleureCouleur;
				break;
			}
			else if(currentColor > startColor)
			{
				resultat.raison = PireCouleur;
				break;
			}

			if(DIGITALIO_Read(BMP_FRONT))
			{
				resultat.raison = Bumper;
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
		stop();

		resultat.distance = (float)nbLeftTotal*PI*WHEEL_DIAMETER/WHEEL_NB_COCHES;

		m_posX += resultat.distance * cos(m_orientation*180*PI);
		m_posY += -resultat.distance * sin(m_orientation*180*PI);

		return resultat;
}
*/

/*
bool Robot::inputInitialConditions()
 {
 	short rawStartPosX  = 0; // Position par defaut X
	bool premierRobot  = true; //Premier robot par defaut
	bool boutonEnfonce = true;

	while(true)
	{
		if(DIGITALIO_Read(BMP_FRONT)) break;

		if(DIGITALIO_Read(BMP_REAR))
		{
			premierRobot = !premierRobot;
			boutonEnfonce = true;
		}

		if(DIGITALIO_Read(BMP_LEFT))
		{
			boutonEnfonce = true;
		}

		if(DIGITALIO_Read(BMP_RIGHT))
 		{
 			boutonEnfonce = true;
 			rawStartPosX = (rawStartPosX+1)%6;
 		}

 		if(boutonEnfonce)
 		{
 			LCD_ClearAndPrint("Position de depart:\n");

			for(int i=0; i<2; ++i)
			{
				for(int j=0; j<6; ++j)
				{
					LCD_Printf("|");

					char pos;
					if((i==0 == premierRobot) && j==rawStartPosX)
					{
						pos = 'X';
					}
					else
					{
						switch(j)
						{
							case 0: pos = '6'; break;
							case 1: pos = '4'; break;
							case 2: pos = '2'; break;
							case 3: pos = '1'; break;
							case 4: pos = '3'; break;
							case 5: pos = '5'; break;
							default: pos = '?'; break;
						}
					}

					LCD_Printf("%c", pos);
				}
				LCD_Printf("|\n");
			}
		}
		boutonEnfonce = false;

		THREAD_MSleep(100);
	}

 	m_startPos = rawStartPosX;
 	m_isFirstRobot = premierRobot;
 	initStartPosition();
 	m_gps->updateWorld();

	return m_isFirstRobot;
}

void Robot::initStartPosition()
{
	switch(m_startPos)
	{
		case 0: m_posX=POS0+START_SQUARE_WIDTH/2; break;
		case 1: m_posX=POS1+START_SQUARE_WIDTH/2; break;
		case 2: m_posX=POS2+START_SQUARE_WIDTH/2; break;
		case 3: m_posX=POS3+START_SQUARE_WIDTH/2; break;
		case 4: m_posX=POS4+START_SQUARE_WIDTH/2; break;
		case 5: m_posX=POS5+START_SQUARE_WIDTH/2; break;
		default: m_posX=POS0+START_SQUARE_WIDTH/2; break;
	}

	m_posY = (m_isFirstRobot) ? TOP_START_AREA+START_SQUARE_LENGTH/2 : MID_START_AREA+START_SQUARE_LENGTH/2;
	m_orientation = 90;
}
*/

void Robot::stopAll()
{
	m_stopAll = true;
	stop();
}

void Robot::setOrientation(float orientation)
{
	//Amener entre -180 et 180
	orientation = fmod(orientation, 360);
	if(orientation > 180) orientation = orientation-360;

	m_orientation = orientation;
}

void Robot::printPosition()
{
	LCD_Printf("Position: %f , %f\nOrientation: %f\n", m_posX, m_posY, m_orientation);
}

bool Robot::demanderGroupeAlimentaire(GroupeAlimentaire groupe)
{
	int choix = choixMenu(SERVO_325);

	return (choix-1==groupe);
}

bool Robot::demanderAliment(GroupeAlimentaire groupe)
{
	int choix = choixMenu(SERVO_605);

	return (choix-1==groupe);
}

void Robot::jeuRecette()
{
    //Definir les recettes
    vector<Recette> recettes;
    initRecettes(recettes);


    //Selectionner une recette au hasard
    int numeroDeRecette = random(0, recettes.size()-1);
    Recette& recette = recettes.at(numeroDeRecette);

    //Afficher la recette
    afficherRecette(recette);

    //Demander groupe alimentaire manquant
    LCD_Printf("Il manque un groupe alimentaire. Lequel?\n");
    bool bonneReponse = demanderGroupeAlimentaire(recette.groupeManquant);

    if(bonneReponse)    LCD_Printf("Bravo!");
    else                LCD_Printf("Faux!");

    LCD_Printf("Le groupe manquant est: %s", toString(recette.groupeManquant).data());

    //Demander un aliment de ce groupe
    LCD_Printf("Quel aliment fait partie des %s",toString(recette.groupeManquant).data());
    bonneReponse = demanderAliment(recette.groupeManquant);

    if(bonneReponse)    LCD_Printf("Bravo!");
    else                LCD_Printf("Faux!");

    LCD_Printf("La bonne reponse est %s", exempleAliment(recette.groupeManquant).data());
}

void Robot::initRecettes(Recette& recettes)
{
	/// Hamburger
	    recettes.push_back(Recette("Hamburger", POULET, LAITUE, FROMAGE, PAIN, VIANDE));
	    recettes.push_back(Recette("Hamburger", POULET, LAITUE, FROMAGE, PAIN, CEREALIER));

	    recettes.push_back(Recette("Hamburger", POULET, TOMATE, FROMAGE, PAIN, VIANDE));
		recettes.push_back(Recette("Hamburger", POULET, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Hamburger", POULET, TOMATE, FROMAGE, PAIN, CEREALIER));

		recettes.push_back(Recette("Hamburger", BOEUF, LAITUE, FROMAGE, PAIN, CEREALIER));

		recettes.push_back(Recette("Hamburger", BOEUF, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Hamburger", BOEUF, TOMATE, FROMAGE, PAIN, CEREALIER));

		///Gateau
		recettes.push_back(Recette("Gateau", OEUF, FRAISE, LAIT, FARINE, LAITIER));

		recettes.push_back(Recette("Gateau", OEUF, CAROTTE, LAIT, FARINE, LAITIER));

		///Dejeuner
		recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, LAIT, CREPE, LAITIER));
		recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, LAIT, CREPE, LEGUME_FRUIT));

		recettes.push_back(Recette("Dejeuner", SAUCISSE, ORANGE, LAIT, CREPE, LAITIER));

		recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, YOGOURT, CREPE, LEGUME_FRUIT));

		recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, LAIT, PAIN, LAITIER));
		recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, LAIT, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, LAIT, PAIN, CEREALIER));

		recettes.push_back(Recette("Dejeuner", SAUCISSE, ORANGE, LAIT, PAIN, LAITIER));
		recettes.push_back(Recette("Dejeuner", SAUCISSE, ORANGE, LAIT, PAIN, CEREALIER));

		recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, YOGOURT, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, YOGOURT, PAIN, CEREALIER));
		/**/
		recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, CREPE, LAITIER));
		recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, CREPE, LEGUME_FRUIT));

		recettes.push_back(Recette("Dejeuner", OEUF, ORANGE, LAIT, CREPE, LAITIER));

		recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, YOGOURT, CREPE, LEGUME_FRUIT));

		recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, PAIN, LAITIER));
		recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, PAIN, CEREALIER));

		recettes.push_back(Recette("Dejeuner", OEUF, ORANGE, LAIT, PAIN, LAITIER));
		recettes.push_back(Recette("Dejeuner", OEUF, ORANGE, LAIT, PAIN, CEREALIER));

		recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, YOGOURT, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, YOGOURT, PAIN, CEREALIER));
		/**/
		recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, LAIT, CREPE, LAITIER));
		recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, LAIT, CREPE, LEGUME_FRUIT));

		recettes.push_back(Recette("Dejeuner", JAMBON, ORANGE, LAIT, CREPE, LAITIER));

		recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, YOGOURT, CREPE, LEGUME_FRUIT));

		recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, LAIT, PAIN, LAITIER));
		recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, LAIT, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, LAIT, PAIN, CEREALIER));

		recettes.push_back(Recette("Dejeuner", JAMBON, ORANGE, LAIT, PAIN, LAITIER));
		recettes.push_back(Recette("Dejeuner", JAMBON, ORANGE, LAIT, PAIN, CEREALIER));

		recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, YOGOURT, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, YOGOURT, PAIN, CEREALIER));

		///Spaghetti (pas assez d'alterations)
		recettes.push_back(Recette("Spaghetti", BOEUF, TOMATE, FROMAGE, PATES, LEGUME_FRUIT));

		///Sandwich
		recettes.push_back(Recette("Sandwich", POULET, TOMATE, FROMAGE, PAIN, VIANDE));
		recettes.push_back(Recette("Sandwich", POULET, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Sandwich", POULET, TOMATE, FROMAGE, PAIN, CEREALIER));

		recettes.push_back(Recette("Sandwich", POULET, LAITUE, FROMAGE, PAIN, VIANDE));
		recettes.push_back(Recette("Sandwich", POULET, LAITUE, FROMAGE, PAIN, CEREALIER));
		/**/
		recettes.push_back(Recette("Sandwich", JAMBON, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Sandwich", JAMBON, TOMATE, FROMAGE, PAIN, CEREALIER));

		recettes.push_back(Recette("Sandwich", JAMBON, LAITUE, FROMAGE, PAIN, CEREALIER));
		/**/
		recettes.push_back(Recette("Sandwich", BACON, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT));
		recettes.push_back(Recette("Sandwich", BACON, TOMATE, FROMAGE, PAIN, CEREALIER));

		recettes.push_back(Recette("Sandwich", BACON, LAITUE, FROMAGE, PAIN, CEREALIER));
}

void Robot::exempleThread()
{
	THREAD t1,t2;

	threadedSay(&t1, 6);	//Create and start threads
	threadedSay(&t2, "Allo");

	pthread_join(t1, NULL);	//Wait until threads ends
	pthread_join(t2, NULL);
}
