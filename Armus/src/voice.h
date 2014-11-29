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

using namespace std;

class Voice
{
    private:
    string audioFileFormat;
    
    public:
    Voice();
    void playAudioFile(string filePath);
    void playNumber(int);
    void playTitle(string title);
    void play(int, string);
    void play(int, string, int);
    void play(string, int);
    void play(string, int, string);
};
#endif
