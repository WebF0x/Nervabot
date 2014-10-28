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

class Robot
{
public:
	Robot();
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
	void inputStartPosition();
	void attendreBruitDepart();
	bool isSecondRobot();
	void ecouterBruitFin();
	void trouverCible();
	void endgame();
	void freeze();
	void initGPS();

	void setOrientation(float orientation);
	void printPosition();

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

private:
	PathFinder* m_gps;
	float m_posX,m_posY;
	float m_orientation;
	short m_startPos;
	bool isFirstRobot;

	static const int PIN_DETECTEUR_SIFFLET = 1;
	static const int THRESHOLD_SIFFLET = 600;

	static const int SPEEDTARGET = 50;
	static const int SPEEDTARGETPRUDENT = 50;

	static const float WHEEL_DIAMETER = 7.6;
	static const int WHEEL_NB_COCHES = 64;
	static const float DISTANCE_ROUES = 14;
	static const float PI = 3.1415926535897932384626433832795;
};

#endif /* ROBOT_H_ */
