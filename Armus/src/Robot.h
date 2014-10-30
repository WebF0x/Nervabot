/*
 * Robot.h
 *
 *  Created on: 2014-10-01
 *  Author: Equipe P4
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libarmus.h>
#include <Math.h>
#include "PathFinder.h"
#include <stdlib.h>
#include <time.h>
#include "capteurCouleur.h"
#include <set>

//Prise de mesures du parcours (A FAIRE)
//Origine en haut a gauche du parcours
#define REAL_WORLD_WIDTH 243.f
#define REAL_WORLD_LENGTH 610.f
#define RED_MARGIN_WIDTH 30.f

#define TOP_START_AREA (REAL_WORLD_LENGTH - 30.f)
#define MID_START_AREA (TOP_START_AREA + (REAL_WORLD_LENGTH - TOP_START_AREA)/2.f)
#define BOT_START_AREA REAL_WORLD_LENGTH

#define START_SQUARE_WIDTH ((REAL_WORLD_WIDTH-2.f*RED_MARGIN_WIDTH)/6.f)
#define START_SQUARE_LENGTH ((REAL_WORLD_LENGTH-TOP_START_AREA)/2.f)

#define POS0 (RED_MARGIN_WIDTH + START_SQUARE_WIDTH*0.f)
#define POS1 (RED_MARGIN_WIDTH + START_SQUARE_WIDTH*1.f)
#define POS2 (RED_MARGIN_WIDTH + START_SQUARE_WIDTH*2.f)
#define POS3 (RED_MARGIN_WIDTH + START_SQUARE_WIDTH*3.f)
#define POS4 (RED_MARGIN_WIDTH + START_SQUARE_WIDTH*4.f)
#define POS5 (RED_MARGIN_WIDTH + START_SQUARE_WIDTH*5.f)

#define OBSTACLE_RAYON 13.f
#define OBSTACLE_GAUCHE_X 60.f
#define OBSTACLE_GAUCHE_Y 228.f
#define OBSTACLE_MILIEU_X 121.f
#define OBSTACLE_MILIEU_Y 274.f
#define OBSTACLE_DROITE_X 182.f
#define OBSTACLE_DROITE_Y OBSTACLE_GAUCHE_Y
#define CIBLE_X OBSTACLE_MILIEU_X
#define CIBLE_Y 122.f

class Robot
{
public:
	Robot(bool isArmu022);
	virtual ~Robot();

	void dispSpeedDifferences();
	void stop();

	void avancer(float distance);
	void tourner(float angle);
	void tournerSurPlace(float angle);

	void endGame();
	int lecture_couleur();
	void writeInFile(const char* filename, const char* text);
	void Attendre5kHz();

	void grandeCourse();
	void inputInitialConditions();
	void initStartPosition();
	void attendreBruitDepart();
	bool isSecondRobot();
	void ecouterBruitFin();
	void trouverCible();
	void endgame();
	void freeze();
	void initGPS();

	void setOrientation(float orientation);
	void printPosition();
	float rayon(int couleur);
	float maxDistToBestColor(int couleur);

	enum Raison
	{
		PireCouleur,
		MeilleureCouleur,
		Bumper,
		DistanceParcourue
	};

	struct Deplacement
	{
		Raison raison;
		int distance;
	};

	Deplacement avancerPrudemment(float distance);
	Deplacement suivreArc(float rayon, bool versDroite, float distance);
	PathFinder* m_gps;

private:

	float m_posX,m_posY;
	float m_orientation;
	short m_startPos;
	bool m_isFirstRobot;

	static const int GPS_RESOLUTION_X = 50;
	static const int GPS_RESOLUTION_Y = 125;

	static const int PIN_DETECTEUR_SIFFLET = 1;
	static const int THRESHOLD_SIFFLET = 600;

	static const int SPEEDTARGET = 50;
	static const int SPEEDTARGETPRUDENT = 50;

	static const float WHEEL_DIAMETER = 7.6;
	static const int WHEEL_NB_COCHES = 64;
	static const float DISTANCE_ROUES = 14;
	static const float PI = 3.1415926535897932384626433832795;

	static const int ROUGE = 4;
	static 	const int BLANC = 3;
	static const int JAUNE = 2;
	static const int VERT = 1;
	static const int BLEU = 0;
	static const float FLECHE_CIBLE = 30.f;

	bool m_isArmu022;
};

#endif /* ROBOT_H_ */
