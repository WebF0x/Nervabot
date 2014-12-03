/*
 * Robot.cpp
 *
 *  Created on: 2014-10-01
 *  Author: Equipe P4
 */

#include "Robot.h"

using namespace std;

Robot::Robot()
{
	AUDIO_SetVolume(100);
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
	stop();
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

float Robot::demanderGroupeAlimentaire(GroupeAlimentaire groupe)
{
    SYSTEM_ResetTimer();
	int choix = choixMenu(SERVO_325);
    
    if(choix-1==groupe)
        return SYSTEM_ReadTimerMSeconds()/1000;
	else
        return false;

	/******* On utilise les bumper au lieu des servo moteur pour des fin de debug *******/
	/*GroupeAlimentaire choix;

    LCD_Printf("Front: Viande\nRear: Legume_fruit\nLeft: Laitier\nRight: Cerealier\n");

	while (true)
	{
		if(DIGITALIO_Read(BMP_FRONT))
		{
			choix = VIANDE;
			break;
		}
		else if (DIGITALIO_Read(BMP_REAR))
		{
			choix = LEGUME_FRUIT;
			break;
		}
		else if (DIGITALIO_Read(BMP_LEFT))
		{
			choix = LAITIER;
			break;
		}
		else if (DIGITALIO_Read(BMP_RIGHT))
		{
			choix = CEREALIER;
			break;
		}
		THREAD_MSleep(100);
	}

	LCD_Printf("Choisi: %i\n", choix);

	return (choix == groupe);*/
}

float Robot::demanderAliment(GroupeAlimentaire groupe)
{
	SYSTEM_ResetTimer();
	int choix = choixMenu(SERVO_605);
    
    if(choix-1==groupe)
        return SYSTEM_ReadTimerMSeconds()/1000;
        else
            return false;


	/******* On utilise les bumper au lieu des servo moteur pour des fin de debug *******/
	/*GroupeAlimentaire choix;

	LCD_Printf("Front: Viande\nRear: Legume_fruit\nLeft: Laitier\nRight: Cerealier\n");

	while (true)
	{
		if(DIGITALIO_Read(BMP_FRONT))
		{
			choix = VIANDE;
			break;
		}
		else if (DIGITALIO_Read(BMP_REAR))
		{
			choix = LEGUME_FRUIT;
			break;
		}
		else if (DIGITALIO_Read(BMP_LEFT))
		{
			choix = LAITIER;
			break;
		}
		else if (DIGITALIO_Read(BMP_RIGHT))
		{
			choix = CEREALIER;
			break;
		}
		THREAD_MSleep(100);
	}

	LCD_Printf("Choisi: %i\n", choix);

	return (choix == groupe);*/
}

// initialisation du jeu nécéssaire
void Robot::initJeu()
{
	_parcours.initRobot(this);

    initRecettes(recettes);
}

// le jeu principale
void Robot::jeuRecette()
{
    bool continuerJouer = true;
    while(continuerJouer)
    {
        LCD_ClearAndPrint("");
        THREAD t1, t2;
        //Attendre le signal avant et arrière
        capteurAttendreDebut();
        
        //Introduction au joueur(context, instruction, et intro au premier pays)
        voice.threadedPlay(&t1, "intro");
        pthread_join(t1, NULL);
        voice.threadedPlay(&t1, "introQuestion");
        pthread_join(t1, NULL);

        int nbPays = 5;//Commence a ce pays
        float tempsPartie = 0;
        bool continuerPartie = true;
        while(continuerPartie)
        {
            voice.playPays(&t1, nbPays);
            pthread_join(t1, NULL);
            float bonneReponse = jeuQuestion();
            tempsPartie += bonneReponse;
            
            //avancer ou reculer et affectant nbPays
            if(bonneReponse)
            {
                nbPays--;
                //Verifie si la partie est terminer
                if(nbPays == 0)
                {
                    voice.threadedPlay(&t1, "gagnePartie");
                    voice.playTempsPartie(&t1, &t1, &t1, tempsPartie);
                    continuerPartie = false;
                }
                else
                {
                    voice.playAvance(&t1);
                    _parcours.deplacer(bonneReponse);
                }
            }
            else
            {
                nbPays++;
                //Verifie si la partie est terminer
                if(nbPays == 8)
                {
                    voice.threadedPlay(&t1, "perdrePartie");
                    continuerPartie = false;
                }
                else
                {
                    voice.playRecule(&t1);
                    _parcours.deplacer(bonneReponse);
                }
            }
        }
    }
}

float Robot::jeuQuestion()
{
	THREAD t1, t2;
    //Selectionner une recette au hasard
    int numeroDeRecette = random(1, recettes.size()-1);
    Recette& recette = recettes.at(numeroDeRecette);

    //Afficher la recette a l'écran
    afficherRecette(recette);

    //L'audio de la recette est joué
    int tempsAudio = voice.playQuestionGroupe(&t1, &t1, &t1, numeroDeRecette);
    //Call bloquant où on attent que le thread ait fini de faire jouer l'audio
    pthread_join(t1, NULL);

    //Demander groupe alimentaire manquant
    LCD_Printf("Il manque un groupe alimentaire. Lequel? \n");
    float bonneReponse = demanderGroupeAlimentaire(recette.groupeManquant);

    direReponse(bonneReponse, recette, numeroDeRecette);

    if (bonneReponse)
    {
		//Demander groupe alimentaire manquant
		LCD_Printf("Quel aliment fait parti du groupe: %s ?\n", toString(recette.groupeManquant).data());
		voice.threadedPlay(&t1, "questionAliment");
		pthread_join(t1, NULL);
        
		bonneReponse = demanderAliment(recette.groupeManquant);
        
        direReponse(bonneReponse, recette, numeroDeRecette);
    }
    return bonneReponse;
}

void Robot::direReponse(bool bonnereponse, Recette recette, int numeroDeRecette)
{
	int flashingTime = 0;
	THREAD t1, t2;

    if(bonnereponse)
    {
    	LCD_Printf("Bravo!\n");
    	flashingTime = voice.playGagne(&t1, &t2);
    	delFlash(DEL_O, flashingTime);
    	pthread_join(t1, NULL);
    }
    else
    {
    	LCD_Printf("Faux!\n");

    	flashingTime = voice.playPerdre(&t1, &t2);
        LCD_Printf("La bonne reponse est: %s ", toString(recette.groupeManquant).data());
    	delFlash(DEL_X, flashingTime);
        pthread_join(t1, NULL);

        voice.playReponseRecette(&t2, numeroDeRecette);
    	pthread_join(t2, NULL);
    }
}

void Robot::initRecettes(vector<Recette>& recettes)
{
    recettes.push_back(Recette("Hamburger", POULET, LAITUE, FROMAGE, PAIN, VIANDE));//Qui comple la case vide
    recettes.push_back(Recette("Hamburger", POULET, LAITUE, FROMAGE, PAIN, VIANDE));//1
    recettes.push_back(Recette("Hamburger", POULET, LAITUE, FROMAGE, PAIN, CEREALIER));//2
    recettes.push_back(Recette("Hamburger", POULET, TOMATE, FROMAGE, PAIN, VIANDE));//3
    recettes.push_back(Recette("Hamburger", POULET, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT));//4
    recettes.push_back(Recette("Hamburger", POULET, TOMATE, FROMAGE, PAIN, CEREALIER));//5
    recettes.push_back(Recette("Hamburger", BOEUF, LAITUE, FROMAGE, PAIN, CEREALIER));//6
    recettes.push_back(Recette("Hamburger", BOEUF, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT));//7
    recettes.push_back(Recette("Gateau", OEUF, FRAISE, LAIT, FARINE, LAITIER));//8
    recettes.push_back(Recette("Gateau", OEUF, CAROTTE, LAIT, FARINE, LAITIER));//9
    recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, LAIT, CREPE, LAITIER));//10
    recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, LAIT, CREPE, LEGUME_FRUIT));//11
    recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, LAIT, PAIN, CEREALIER));//12
    recettes.push_back(Recette("Dejeuner", SAUCISSE, ORANGE, LAIT, PAIN, LAITIER));//13
    recettes.push_back(Recette("Dejeuner", SAUCISSE, ORANGE, LAIT, PAIN, CEREALIER));//14
    recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, YOGOURT, PAIN, LEGUME_FRUIT));//15
    recettes.push_back(Recette("Dejeuner", SAUCISSE, TOMATE, YOGOURT, PAIN, CEREALIER));//16
    recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, CREPE, LAITIER));//17
    recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, CREPE, LEGUME_FRUIT));//18
    recettes.push_back(Recette("Dejeuner", OEUF, ORANGE, LAIT, CREPE, LAITIER));//19
    recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, YOGOURT, CREPE, LEGUME_FRUIT));//20
    recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, PAIN, LAITIER));//21
    recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, PAIN, LEGUME_FRUIT));//22
    recettes.push_back(Recette("Dejeuner", OEUF, TOMATE, LAIT, PAIN, CEREALIER));//23
    recettes.push_back(Recette("Dejeuner", OEUF, ORANGE, LAIT, PAIN, LAITIER));//24
    recettes.push_back(Recette("Dejeuner", OEUF, ORANGE, LAIT, PAIN, CEREALIER));//25
    recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, LAIT, CREPE, LAITIER));//26
    recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, LAIT, CREPE, LEGUME_FRUIT));//27
    recettes.push_back(Recette("Dejeuner", JAMBON, TOMATE, YOGOURT, PAIN, CEREALIER));//28
    recettes.push_back(Recette("Spaghetti", BOEUF, TOMATE, FROMAGE, PATES, LEGUME_FRUIT));//29
    recettes.push_back(Recette("Sandwich", POULET, TOMATE, FROMAGE, PAIN, VIANDE));//30
    recettes.push_back(Recette("Sandwich", POULET, TOMATE, FROMAGE, PAIN, CEREALIER));//31
    recettes.push_back(Recette("Sandwich", POULET, LAITUE, FROMAGE, PAIN, VIANDE));//32
    recettes.push_back(Recette("Sandwich", JAMBON, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT));//33
    recettes.push_back(Recette("Sandwich", JAMBON, TOMATE, FROMAGE, PAIN, CEREALIER));//34
    recettes.push_back(Recette("Sandwich", BACON, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT));//35
    recettes.push_back(Recette("Sandwich", BACON, TOMATE, FROMAGE, PAIN, CEREALIER));//36
    recettes.push_back(Recette("Sandwich", BACON, LAITUE, FROMAGE, PAIN, CEREALIER));//37
}

void Robot::exempleThread()
{
	THREAD t1,t2;

	threadedSay(&t1, 6);	//Create and start threads
	threadedSay(&t2, "Allo");

	pthread_join(t1, NULL);	//Wait until threads ends
	pthread_join(t2, NULL);
}
