/*
 * Robot.cpp
 *
 *  Created on: 2014-10-01
 *  Author: Equipe P4
 */

#include "Robot.h"

using namespace std;

Robot::Robot(bool isArmu022) : m_isArmu022(isArmu022)
{
	initGPS();

	if(isArmu022) initB();
	else initA();
}

Robot::~Robot()
{
	delete m_gps;
}

void Robot::initGPS()
{
	m_gps = new PathFinder(GPS_RESOLUTION_X, GPS_RESOLUTION_Y, REAL_WORLD_WIDTH, REAL_WORLD_LENGTH);

	pair<int,int> boxCible = m_gps->pointToBox(CIBLE_X,CIBLE_Y);
	m_gps->addGoal(boxCible.first,boxCible.second);

	/// If the center of a box is  inside an obstacle, this box is a death
	set<pair<float,float> > obstacles;
	obstacles.insert(make_pair(OBSTACLE_GAUCHE_X,OBSTACLE_GAUCHE_Y));
	obstacles.insert(make_pair(OBSTACLE_MILIEU_X,OBSTACLE_MILIEU_Y));
	obstacles.insert(make_pair(OBSTACLE_DROITE_X,OBSTACLE_DROITE_Y));

	for(set<pair<float,float> >::iterator obstacle=obstacles.begin(); obstacle!=obstacles.end(); ++obstacle)	//For each obstacle
	{
		set<pair<int,int> > boxesToCheck;
		boxesToCheck.insert(m_gps->pointToBox(obstacle->first, obstacle->second));	//first box is the one containing the obstacle's center

		while(!boxesToCheck.empty())
		{
			set<pair<int,int> > nextBoxes;

			for(set<pair<int,int> >::iterator box=boxesToCheck.begin(); box!=boxesToCheck.end(); ++box) //For each box to check
			{
				//Take the center of the box
				pair<float,float> center  = m_gps->boxToPoint(box->first, box->second);
				float x = center.first;
				float y = center.second;
				float deltaX = obstacle->first - x;
				float deltaY = obstacle->second - y;
				bool isInsideObstacle = (deltaX*deltaX + deltaY*deltaY <= OBSTACLE_RAYON*OBSTACLE_RAYON);

				if(isInsideObstacle)
				{
					m_gps->addDeath(box->first,box->second);

					nextBoxes.insert(make_pair(x+1,y));
					nextBoxes.insert(make_pair(x-1,y));
					nextBoxes.insert(make_pair(x,y+1));
					nextBoxes.insert(make_pair(x,y-1));
				}
			}
			boxesToCheck = nextBoxes;
		}
	}
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
	if(m_isArmu022) return getCurrentColorB();
	else return getCurrentColorA();
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
	inputInitialConditions();
	m_gps->updateWorld();
	attendreBruitDepart();
	if(!m_isFirstRobot) attendreBruitDepart();	//Attendre le deuxieme sifflet de depart

	//THREAD( ecouterBruitFin() )

	//Debut de la course
	trouverCible();
	endGame();
}

void Robot::inputInitialConditions()
 {
 	short rawStartPosX  = 0; // Position par defaut X
	bool premierRobot  = true; //Premier robot par defaut
	bool boutonEnfonce = true;

	while(true)
 	{
		if(DIGITALIO_Read(BMP_FRONT))
		{
			boutonEnfonce = true;
			break;
		}

		if(DIGITALIO_Read(BMP_REAR))
 		{
 			premierRobot = !premierRobot;
 			boutonEnfonce = true;
 		}

		if(DIGITALIO_Read(BMP_LEFT))
 		{
 			boutonEnfonce = true;
			rawStartPosX --;
			if(rawStartPosX < 0)
			{
				rawStartPosX = 5;
			}
 		}

		if(DIGITALIO_Read(BMP_RIGHT))
 		{
 			boutonEnfonce = true;
 			rawStartPosX = (rawStartPosX+1)%6;
 		}

 		if(boutonEnfonce)
 		{
			LCD_Printf("Position de depart:\n");
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

 }

void Robot::initStartPosition()
{
	setOrientation(90.f);

	switch(m_startPos)
	{
		case 0: m_posX=POS0+START_SQUARE_WIDTH/2.f; break;
		case 1: m_posX=POS1+START_SQUARE_WIDTH/2.f; break;
		case 2: m_posX=POS2+START_SQUARE_WIDTH/2.f; break;
		case 3: m_posX=POS3+START_SQUARE_WIDTH/2.f; break;
		case 4: m_posX=POS4+START_SQUARE_WIDTH/2.f; break;
		case 5: m_posX=POS5+START_SQUARE_WIDTH/2.f; break;
		default: m_posX=POS0+START_SQUARE_WIDTH/2.f; break;
	}

	m_posY = (m_isFirstRobot) ? TOP_START_AREA+START_SQUARE_LENGTH/2 : MID_START_AREA+START_SQUARE_LENGTH/2;
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
	while(true)
	{
		pair<float,float> destination = m_gps->nextWaypoint(m_posX, m_posY);
		float x2 = destination.first;
		float y2 = destination.second;
		float a = x2-m_posX;
		float b = y2-m_posY;

		/*
		LCD_Printf("Position: %f , %f\n",m_posX,m_posY );
		LCD_Printf("Destination: %f , %f\n",x2,y2 );
		m_gps->debug();
		//*/

		float distanceVoulue = sqrt(a*a + b*b);

		float orientationVoulue = atan(b/a);	//http://bv.alloprof.qc.ca/mathematique/geometrie/les-vecteurs/le-vecteur-dans-un-plan-cartesien-et-ses-composantes.aspx#orientationcompo
		if(a<0) orientationVoulue+=180;
		else if(b<0) orientationVoulue+=360;

		float angleVirage = orientationVoulue-m_orientation;
		//Ramener entre -180 et 180
		angleVirage = fmod(angleVirage, 360);
		if(angleVirage > 180) angleVirage = angleVirage-360 ;

		tournerSurPlace(angleVirage);
		Deplacement d = avancerPrudemment(distanceVoulue);
		switch(d.raison)
		{
			case DistanceParcourue:
			{
				//Parfait, passer au prochain waypoint
				break;
			}
			case PireCouleur:
			{
				//On touche la bande rouge, quoi faire? C'est pas sense arriver...Peut-etre ajuster notre m_posX...
				break;
			}
			case MeilleureCouleur:
			{
				//Cible trouvee! La seule raison de quitter la fonction
				return;
			}
			case Bumper:
			{
				pair<int,int> box = m_gps->pointToBox(m_posX, m_posY);
				int boxX = box.first;
				int boxY = box.second;

				if(45 <= m_orientation && m_orientation <= 135)	//North is bad!
				{
					m_gps->addDeath(boxX, boxY-1);
				}
				else if(-135 <= m_orientation && m_orientation <= -45)	//South is bad!
				{
					m_gps->addDeath(boxX, boxY+1);
				}
				else if(135 <= m_orientation || m_orientation <= -135)	//West is bad!
				{
					m_gps->addDeath(boxX-1, boxY);
				}
				else if(-45 <= m_orientation || m_orientation <= 45)	//East is bad!
				{
					m_gps->addDeath(boxX+1, boxY);
				}

				m_gps->updateWorld();

				break;
			}
		}
	}
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


