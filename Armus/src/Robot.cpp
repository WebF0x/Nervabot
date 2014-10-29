/*
 * Robot.cpp
 *
 *  Created on: 2014-10-01
 *  Author: Equipe P4
 */

#include "Robot.h"

Robot::Robot()
{
	initGPS();
}

Robot::~Robot()
{
	delete m_gps;
}

void Robot::initGPS()
{
	int worldWidth = 1;
	int worldLength = 1;

	m_gps = new PathFinder(worldWidth, worldLength);

	m_gps->addGoal(0,0);

	m_gps->addDeath(1,1);
	m_gps->addDeath(1,1);
	m_gps->addDeath(2,1);
	m_gps->addDeath(3,1);
	m_gps->addDeath(1,2);
	m_gps->addDeath(3,2);
	m_gps->addDeath(2,3);
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

/*
 * Si vous avez besoin de la position et l'orientation du robot, preferez la fonction tournerSurPlace()
 */
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

//Angle entre -180 et 180
void Robot::tournerSurPlace(float angle)
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

/*
 * A tester
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
	return 0;
}

int random(int low, int high)
{
	srand(time(NULL));
	return rand() % (high - low + 1) + low;
}
/*
 * Je m<excuse Jesus pour cette longue fonction
 */
void Robot::endGame()
{
	int couleur_present = JAUNE;
	int nb_Coche = 0;

	while(lecture_couleur() == couleur_present && couleur_present != BLEU)
	{
		bool returnToYolo = false;
		//Point: yolo
		Deplacement d = avancerPrudemment(maxDistToBestColor(couleur_present));

		switch(d.raison)
		{
			case DistanceParcourue:
			{
				tournerSurPlace(90);
				Deplacement d2 = suivreArc(maxDistToBestColor(couleur_present), true, 300);	//Aucune idee de vers droite ou pas, fais juste continuer pour trouver une autre couleur
				switch(d2.raison)
				{
					case MeilleureCouleur:	//Exactly according to the plan
					{
						--couleur_present;
						returnToYolo = true;
						break;
					}
					case DistanceParcourue:	//WTF
					{
						returnToYolo=true;
						break;
					}
					case PireCouleur:
					{
						tournerSurPlace(180);
						returnToYolo=true;
						break;
					}
					case Bumper:
					{
						do
						{
							tournerSurPlace(random(-180, 180));
							d2 = avancerPrudemment(300); //Avance a l'infini
						}while(d2.raison == Bumper);

						if(d2.raison==PireCouleur)
						{
							tournerSurPlace(180);
							returnToYolo = true;
							break;
						}
						else if (d2.raison==MeilleureCouleur)
						{
							--couleur_present;
							returnToYolo = true;
							break;
						}

						break;
					}
				}
				break;
			}

			case MeilleureCouleur:
			{
				--couleur_present;
				returnToYolo = true;
				break;
			}

			case Bumper:
			{
				while(d.raison == Bumper)
				{
					tournerSurPlace(random(-180, 180));
					d = avancerPrudemment(300); //Avance a l'infini
				}

				if(d.raison==PireCouleur)
				{
					tournerSurPlace(180);
					returnToYolo = true;
					break;
				}
				else if (d.raison==MeilleureCouleur)
				{
					--couleur_present;
					returnToYolo = true;
					break;
				}

				break;
			}

			case PireCouleur:	//Oops mauvaise hypothese, je suis retourner sur l'arc
			{
				int corde = d.distance;
				tournerSurPlace(180);
				Deplacement d2 = avancerPrudemment(corde/2);	//Attention calculer si cest la bonne distance (a cause de difference entre capteur et centre de roues
				switch(d2.raison)
				{
					case Bumper:
					{
						while(d2.raison == Bumper)
						{
							tournerSurPlace(random(-180, 180));
							d2 = avancerPrudemment(300); //Avance a l'infini
						}

						if(d2.raison==PireCouleur)
						{
							tournerSurPlace(180);
							returnToYolo = true;
							break;
						}
						else if (d2.raison==MeilleureCouleur)
						{
							--couleur_present;
							returnToYolo = true;
							break;
						}

						break;
					}
					case PireCouleur:
					{
						tournerSurPlace(180);
						returnToYolo = true;
						break;
					}
					case MeilleureCouleur:
					{
						--couleur_present;
						returnToYolo = true;
						break;
					}
					case DistanceParcourue:
					{
						//On est au centre d'une corde
						tournerSurPlace(90);
						bool returnToHashTag = false;
						do
						{
							//Point: HashTag
							Deplacement d3 = avancerPrudemment(sqrt(rayon(couleur_present)*rayon(couleur_present) - corde * corde / 4));
							switch(d3.raison)
							{
								case DistanceParcourue:
								{
									//wtf a guess on s'est fait tasse
									{
										do
										{
											tournerSurPlace(random(-180, 180));
											d2 = avancerPrudemment(300); //Avance a l'infini
										}while(d2.raison == Bumper);

										if(d2.raison==PireCouleur)
										{
											tournerSurPlace(180);
											returnToYolo = true;
											break;
										}
										else if (d2.raison==MeilleureCouleur)
										{
											--couleur_present;
											returnToYolo = true;
											break;
										}

										break;
									}
								}
								case MeilleureCouleur:
								{
									//Sur le bon chemin!
									--couleur_present;
									returnToYolo = true;
									break;
								}
								case PireCouleur:
								{
									//Whoops mauvais bord
									tournerSurPlace(180);
									returnToYolo = true;
								}
								case Bumper:
								{
									//Aww on allait vers le centre pourtant snif snif
									tournerSurPlace(90);
									d3 = suivreArc(rayon(couleur_present)-d2.distance, true, 60); //60 = A peu pres 2 largeur de robot
									switch(d3.raison)
									{
										case Bumper: //God fucking damnit, rage quit j,essaye nimporte quoi
										{
											do
											{
												tournerSurPlace(random(-180, 180));
												d2 = avancerPrudemment(300); //Avance a l'infini
											}while(d2.raison == Bumper);

											if(d2.raison==PireCouleur)
											{
												tournerSurPlace(180);
												returnToYolo = true;
												break;
											}
											else if (d2.raison==MeilleureCouleur)
											{
												--couleur_present;
												returnToYolo = true;
												break;
											}

											break;
										}
										case DistanceParcourue:	//reessaye de penetrer la cible
										{
											tournerSurPlace(-90);
											returnToHashTag = true;
											break;
										}
										case PireCouleur:	//Wtf cest meme pas sense arriver
										{
											tournerSurPlace(180);
											returnToYolo = true;
											break;
										}
										case MeilleureCouleur:	//Wtf cest meme pas sense arriver mais fuck yeah!
										{
											--couleur_present;
											returnToYolo = true;
											break;
										}
									}
									if(returnToYolo) break;
								}
							}
							if(returnToYolo) break;
						}while(returnToHashTag);
					}
				}
				break;
			}
		}
	}
	avancerPrudemment(300);
}

float Robot::rayon(int couleur)
{
	if(couleur==BLEU) return 15.5f;
	else if(couleur==VERT) return 45.5f;
	else return 76.0f; //Jaune
}

float Robot::maxDistToBestColor(int couleur)
{
	float r = rayon(couleur);
	return sqrt((2*r-FLECHE_CIBLE)*FLECHE_CIBLE);
}

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

		resultat.distance = nbLeftTotal*PI*WHEEL_DIAMETER/WHEEL_NB_COCHES;

		m_posX += resultat.distance * cos(m_orientation);
		m_posY += resultat.distance * sin(m_orientation);

		return resultat;
}

void Robot::grandeCourse()
{
	inputStartPosition();
	m_gps->updateWorld();
	attendreBruitDepart();
	if(!isFirstRobot) attendreBruitDepart();

	//THREAD( ecouterBruitFin() )

	//Debut de la course
	trouverCible();
	endGame();
}

void Robot::inputStartPosition()
{
	short rawStartPosX  = 0; // Position par défaut X
	bool  premierRobot  = true; //Premier robot par défaut
	bool  fini 		    = false;
	bool  boutonEnfonce = true;

	while(!fini)
	{
		if(DIGITALIO_Read(BMP_FRONT))
		{
			fini = true;
		}
		else if(DIGITALIO_Read(BMP_REAR))
		{
			premierRobot = !premierRobot;
			boutonEnfonce = true;
		}
		else if(DIGITALIO_Read(BMP_LEFT))
		{
			boutonEnfonce = true;
			rawStartPosX --;
			if(rawStartPosX < 0)
			{
				rawStartPosX = 5;
			}
		}
		else if(DIGITALIO_Read(BMP_RIGHT))
		{
			boutonEnfonce = true;
			rawStartPosX = (rawStartPosX+1)%6;
		}

		if(boutonEnfonce)
		{
			if (premierRobot)
			{
				LCD_Printf("Premier robot, position: %i\n", rawStartPosX+1);
			}
			else
			{
				LCD_Printf("Deuxieme robot, position: %i\n", rawStartPosX+1);
			}
		}
		boutonEnfonce = false;

		THREAD_MSleep(100);
	}

	m_startPos = rawStartPosX;
	isFirstRobot = premierRobot;
}

void Robot::Attendre5kHz()
{
	while(ANALOG_Read(PIN_DETECTEUR_SIFFLET) < THRESHOLD_SIFFLET)
	{
		THREAD_MSleep(100);
	}
}

void Robot::attendreBruitDepart()
{
	Attendre5kHz();
}

void Robot::ecouterBruitFin()
{
	THREAD_MSleep((60*3 - 10) * 1000); //Attendre un peu moins de 3 minutes (duree de la course)
	Attendre5kHz();
	freeze();
}

void Robot::trouverCible()
{

	/*
	cibleTrouvee = false;
	while(!cibleTrouvee)
	{
		raisonStop = avancerPrudemment(ouLeGpsDit)
		si(raisonStop == Bumper ou PireCouleur)
			m_gps->ajouterObstacle(enAvantDuRobot)
			m_gps->updateWorld()
		si(raisonStop == DistanceParcourue) rien
		si(raisonStop == MeilleureCouleur)
			cibleTrouvee=true
	}
	*/
}

void Robot::freeze()
{
	stop();
	//FPGA_StopAll();
}

void Robot::setOrientation(float orientation)
{
	//Amener entre -180 et 180
	orientation = fmod(orientation, 360);
	if(orientation > 180) orientation = -(orientation-180);

	m_orientation = orientation;
}

void Robot::printPosition()
{
	LCD_Printf("Position: %f , %f\nOrientation: %f", m_posX, m_posY, m_orientation);
}


