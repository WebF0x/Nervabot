//
//  voiceClass.h
//  voiceClass
//
//  Created by Jérémie Bonsant on 2014-11-29.
//  Copyright (c) 2014 JeremieBonsant. All rights reserved.
//

#ifndef VOICE_H_
#define VOICE_H_

#include <iostream>
#include <string>
#include <unistd.h>
#include <queue>

#include <libarmus.h>
#include "audioFileInfo.h"

class Voice
{
    private:
    std::string audioFileFormat;
    std::string andioFileDirectory;
 
    audioFileInfo info;

    void playNumber(int cent, int number);
    
public:
    Voice();

    //Jouer un fichier en parall�le dans un thread
    bool threadedPlay(THREAD* thread, std::string fileName);

    int play(THREAD* thread, int);	//Jouer un nombre
    int playQuestionGroupe(THREAD* thread, THREAD* thread2, THREAD* thread3,  int numeroRecette);
    int playReponseRecette(THREAD* thread, int numeroRecette);
    int playPerdre(THREAD* thread1, THREAD* thread2);
    int playGagne(THREAD* thread1, THREAD* thread2);
    int playPays(THREAD* thread1, int numeroPays);
    int playAvance(THREAD* thread1);
    int playRecule(THREAD* thread1);
    int playTempsQuestion(THREAD* thread1, THREAD* thread2, THREAD* thread3, float tempsQuestion);
    int playTempsPartie(THREAD* thread1, THREAD* thread2, THREAD* thread3, float tempsPartie);
    

    //Return duration of file in ms or -1 if fine ddint exist
    int getFileDuration(string fileName);

private:
    int m_threadID;

    int play(std::string fileName, int id);	//Toujours appeler cette methode dans un thread sinon elle bloque l'execution du programme

    /* To use a thread we must pass as parameters a pointer to itself and our parameters */
	template <typename T>
	struct ThreadArg
	{
		Voice * voicePtr;
		T var;
		int id;
	};

	//This method takes care of freeing up "arg"
	template<typename T>
	static void * InternalThreadEntryPassArg(void * arg)
	{
		ThreadArg<T> arguments;
		arguments.voicePtr = ((ThreadArg<T> *)arg)->voicePtr;
		arguments.var = ((ThreadArg<T> *)arg)->var;
		arguments.id = ((ThreadArg<T> *)arg)->id;

		arguments.voicePtr->play(arguments.var, arguments.id);

		delete ((ThreadArg<T> *)arg);
		return NULL;
	}
};
#endif
