//
//  voiceClass.cpp
//  voiceClass
//
//  Created by Jérémie Bonsant on 2014-11-29.
//  Copyright (c) 2014 JeremieBonsant. All rights reserved.
//

#include "voice.h"



int random2(int low, int high)
{
	srand(time(NULL));
	return rand() % (high - low + 1) + low;
}

Voice::Voice()
{
    audioFileFormat = ".wav";
    andioFileDirectory = "/audifile/";
}

int Voice::play(string fileName)
{
    fileName = fileName+audioFileFormat;
    AUDIO_PlayFile(fileName.data());
    THREAD_MSleep(int(info.duration[fileName]*1000-200));
    return 0;
}

int Voice::play(int number)
{
    if(number <= 100 || number%100 == 0 )
    {
        char buffer[4];
        snprintf(buffer, 10, "%d", number);
        string temp;
        temp = buffer;
        temp = temp;
        play(temp);
    }
    else if(number <= 1000)
    {
        play(number - number%100);
        number = number%100;
        if(number > 0)
            play(number);
    }
    else
        return 1;
    return 0;
}

int Voice::playQuestionRecette(int numeroRecette)
{
    char buffer[4];
    snprintf(buffer, 10, "%d", numeroRecette);
    string temp;
    temp = "recette";
    temp = temp+buffer;
    play(temp);
    return 0;
}
int Voice::playReponseRecette(int numeroRecette)
{
    char buffer[4];
    snprintf(buffer, 10, "%d", numeroRecette+1);
    string temp, temp2;
    temp = "recette";
    temp2 = "reponse";
    temp = temp+buffer+temp2;
    play(temp);
    return 0;
}
int Voice::playPerdre()
{
    char buffer[4];
    int i = random2(1,3);
    snprintf(buffer, 10, "%d", i);
    string temp;
    temp = "perdre";
    temp = temp+buffer;
    play(temp);
    return 0;
}
int Voice::playGagne()
{
    char buffer[4];
    int i = random2(1,3);
    snprintf(buffer, 10, "%d", i);
    string temp;
    temp = "gagne";
    temp = temp+buffer;
    play(temp);
    return 0;
}
int Voice::playFact()
{
    char buffer[4];
    int i = random2(1,info.nbFact);
    snprintf(buffer, 10, "%d", i);
    string temp;
    temp = "fact";
    temp = temp+buffer;
    play(temp);
    return 0;
}











