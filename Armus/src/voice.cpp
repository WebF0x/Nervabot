//
//  voiceClass.cpp
//  voiceClass
//
//  Created by Jérémie Bonsant on 2014-11-29.
//  Copyright (c) 2014 JeremieBonsant. All rights reserved.
//

#include "voice.h"



Voice::Voice()
{
    audioFileFormat = ".wav";
    andioFileDirectory = "/audifile/";
}

int Voice::play(string fileName)
{
    fileName = fileName+audioFileFormat;
    AUDIO_PlayFile(fileName.data());
    sleep(info.duration[fileName]+1);
    return 0;
}

int Voice::play(int number)
{
    if(number <= 100 || number%100 == 0 )
    {
        string temp;
        temp = ("%d", number);
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








