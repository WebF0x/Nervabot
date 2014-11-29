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

using namespace std;



class Voice
{
    private:
    string audioFileFormat = ".mp3";
    string andioFileDirectory = "/audifile/";
    void playNumber(int cent, int number);
    
    public:
    Voice();
    int play(string fileName);
    int play(int);
    int play(int, string);
    int play(string, int);
    int play(string, string, string);
    int play(int, string, string);
    int play(string, int, string);
    int play(string, string, int);
    int play(int, int, int);
    int play(string, int, int);
    int play(int, string, int);
    int play(int, int, string);
    

    
    //Return duration of file in ms or -1 if fine ddint exist
    int getFileDuration(string fileName);
};
#endif
