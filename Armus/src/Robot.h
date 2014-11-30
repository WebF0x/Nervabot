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
#include <string>

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
	void initRecettes(std::vector<Recette>& recettes);
	void exempleThread();

	/** Returns true if the thread was successfully started, false if there was an error starting the thread */
	template<typename T>
	bool threadedSay(THREAD* thread, T valeur)
	{
		ThreadArg<T>* arg = new ThreadArg<T>();
		arg->robotPtr = this;
		arg->var = valeur;

		return (pthread_create(thread, NULL, InternalThreadEntryPassArg<T>, arg) == 0);
	}

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

	/* To use a thread we must pass as parameteres a pointer to itself and our parameters */
	template <typename T>
	struct ThreadArg
	{
		Robot * robotPtr;
		T var;
	};

	/* Si on utilise pas LCD_Printf(),
	 * on va pouvoir utiliser:
	 *
	 * template<typename T>
	 * say(T var)
	 * {
	 * 		//Do something with var, independently of its type
	 * }
	 */
	void say(int valeur)
	{
		//*CODE A JÉ//
		//Currently placeholder code//
		LCD_Printf("Debut Say\n");
		for(int i=0; i<3; ++i)
		{
			LCD_Printf("%d: %d\n", i, valeur);
		}
		LCD_Printf("Fin Say\n");
	}
	void say(std::string str)
	{
		//*CODE A JÉ//
		//Currently placeholder code//
		LCD_Printf("Debut Say\n");
		for(int i=0; i<3; ++i)
		{
			LCD_Printf("%d: %s\n", i, str.data());
		}
		LCD_Printf("Fin Say\n");
	}

	//This method takes care of freeing up "arg"
	template<typename T>
	static void * InternalThreadEntryPassArg(void * arg)
	{
		ThreadArg<T> arguments;
		arguments.robotPtr = ((ThreadArg<T> *)arg)->robotPtr;
		arguments.var = ((ThreadArg<T> *)arg)->var;

		arguments.robotPtr->say(arguments.var);

		delete ((ThreadArg<T> *)arg);
		return NULL;
	}
};

#endif /* ROBOT_H_ */
