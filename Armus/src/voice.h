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

#include <libarmus.h>
#include "audioFileInfo.h"
#include "Robot.h"

using namespace std;



class Voice
{
    private:
    string audioFileFormat;
    string andioFileDirectory;
 
    audioFileInfo info;

    void playNumber(int cent, int number);
    
    public:
    Voice();
    int play(string fileName);
    int play(int);
    int playQuestionRecette(int numeroRecette);
    int playReponseRecette(int numeroRecette);
    int playPerdre();
    int playGagne();
    int playFact();
    //Return duration of file in ms or -1 if fine ddint exist
    int getFileDuration(string fileName);
};
#endif
