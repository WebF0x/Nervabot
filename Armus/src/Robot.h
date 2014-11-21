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
#include <stdlib.h>
#include <time.h>
#include "capteurCouleur.h"
#include <set>
#include <vector>
#include "Recette.h"
#include "Servomoteur.h"

class Robot
{
public:
	Robot(bool isArmu022);

	void dispSpeedDifferences();
	void stop();

	void avancer(float distance);
	void tourner(float angle);
	void tournerSurPlace(float angle);

	int lecture_couleur();
	void writeInFile(const char* filename, const char* text);

	//bool inputInitialConditions();
	//void initStartPosition();
	bool isSecondRobot();
	void stopAll();

	void setOrientation(float orientation);
	void printPosition();

	float getX(){return m_posX;}
	float getY(){return m_posY;}

	bool demanderGroupeAlimentaire(GroupeAlimentaire groupe);
	bool demanderAliment(GroupeAlimentaire groupe);
	void jeuRecette();

	/*
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
		float distance;
	};

	Deplacement avancerPrudemment(float distance);
	Deplacement suivreArc(float rayon, bool versDroite, float distance);
	*/

private:

	float m_posX,m_posY;
	float m_orientation;
	short m_startPos;
	bool m_isFirstRobot;
	bool m_stopAll;

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
