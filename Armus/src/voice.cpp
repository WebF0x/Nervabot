//
//  voiceClass.cpp
//  voiceClass
//
//  Created by Jérémie Bonsant on 2014-11-29.
//  Copyright (c) 2014 JeremieBonsant. All rights reserved.
//

#include "voice.h"


Voice::Voice()
{}

int Voice::play(string fileName)
{
    fileName = andioFileDirectory + fileName + audioFileFormat;
    cout << "PLAY : " + fileName << endl;
    sleep(getFileDuration(fileName));
    return 0;
}

int Voice::play(int number)
{
    if(number <= 100 || number%100 == 0 )
        play(to_string(number));
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

int Voice::getFileDuration(string fileName)
{
    return 3;
}

int Voice::play(int A, string B)
{
    play(A);
    play(B);
    return 0;
}
int Voice::play(string A, int B)
{
    play(A);
    play(B);
    return 0;
}
int Voice::play(string A, string B, string C)
{
    play(A);
    play(B);
    play(C);
    return 0;
}
int Voice::play(int A, string B, string C)
{
    play(A);
    play(B);
    play(C);
    return 0;
}
int Voice::play(string A, int B, string C)
{
    play(A);
    play(B);
    play(C);
    return 0;
}
int Voice::play(string A, string B, int C)
{
    play(A);
    play(B);
    play(C);
    return 0;
}
int Voice::play(int A, int B, int C)
{
    play(A);
    play(B);
    play(C);
    return 0;
}
int Voice::play(string A, int B, int C)
{
    play(A);
    play(B);
    play(C);
    return 0;
}
int Voice::play(int A, string B, int C)
{
    play(A);
    play(B);
    play(C);
    return 0;
}
int Voice::play(int A, int B, string C)
{
    play(A);
    play(B);
    play(C);
    return 0;
}







