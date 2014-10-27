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

class Robot
{
public:
	Robot();
	virtual ~Robot();

	void dispSpeedDifferences();
	void stop();

	void avancer(float distance);
	void tourner(float angle);

	void endGame();
	int lecture_couleur();
	void writeInFile(const char* filename, const char* text);
	void Attendre5kHz();

	enum class Raison
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
	float m_leftWheelSlope;
	float m_rightWheelSlope;
	float m_leftWheelOffset;
	float m_rightWheelOffset;

	static const float WHEEL_DIAMETER = 7.6;
	static const int WHEEL_NB_COCHES = 64;
	static const float DISTANCE_ROUES = 13.8;
	static const float PI = 3.1415926535897932384626433832795;

	static const int SPEEDTARGET = 50;
	static const int SPEEDTARGETPRUDENT = 40;
};

#endif /* ROBOT_H_ */
