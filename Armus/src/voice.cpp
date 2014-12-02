//
//  voiceClass.cpp
//  voiceClass
//
//  Created by J√©r√©mie Bonsant on 2014-11-29.
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
	m_threadID = 0;
    audioFileFormat = ".wav";
    andioFileDirectory = "/audifile/";
}

bool Voice::threadedPlay(THREAD* thread, std::string fileName)
{
	ThreadArg<string>* arg = new ThreadArg<string>();
	arg->voicePtr = this;
	arg->var = fileName;
	arg->id = m_threadID;

	THREAD_MSleep(10);	//Sans le sleep Áa, le robot dit parfois les questions ‡ l'envers (je sais pas pourquoi, alors on laisse le sleep...)

	++m_threadID;

	return (pthread_create(thread, NULL, InternalThreadEntryPassArg<string>, arg) == 0);
}

int Voice::play(string fileName, int id)
{
	static queue<int> queue;		//Waiting queue
	queue.push(id);

	while(id != queue.front());	//Wait until you're first

	//It's your turn to talk!
	string fileNameWAV = fileName + audioFileFormat;
	AUDIO_PlayFile(fileNameWAV.data());
	THREAD_MSleep(getFileDuration(fileName));
    
	//I'm done talking
	queue.pop();

	return 0;
}

int Voice::play(THREAD* thread, int number)
{
	LCD_Printf("%d\n",number);
    if(number <= 100 || number%100 == 0 )
    {
        char buffer[4];
        snprintf(buffer, 10, "%d", number);
        string temp;
        temp = buffer;
        temp = temp;
        threadedPlay(thread, temp);
    }
    else if(number <= 1000)
    {
    	play(thread, number - number%100);
        number = number%100;

        if(number > 0)
        	play(thread, number);
    }
    else
        return 1;

    return 1000;
}


int Voice::playQuestionRecette(THREAD* thread1, THREAD* thread2, THREAD* thread3, int numeroRecette)
{
    char buffer1[4];
    int i = random2(1,3);
    snprintf(buffer1, 10, "%d", i);
    string temp1;
    temp1 = "questionRecette";
    temp1 = temp1+buffer1;
    threadedPlay(thread1, temp1);
    
    char buffer2[4];
    snprintf(buffer2, 10, "%d", numeroRecette);
    string temp2;
    temp2 = "recette";
    temp2 = temp2+buffer2;
    threadedPlay(thread2, temp2);

    string temp3;
    temp3 = "questionRecetteFin";
    threadedPlay(thread3, temp3);

    return getFileDuration(temp1)+getFileDuration(temp2)+getFileDuration(temp3);
}

int Voice::playReponseRecette(THREAD* thread, int numeroRecette)
{
    char buffer[4];
    snprintf(buffer, 10, "%d", numeroRecette);
    string temp, temp2;
    temp = "recette";
    temp2 = "reponse";
    temp = temp+buffer+temp2;
    threadedPlay(thread, temp);
    return getFileDuration(temp);
}
int Voice::playPerdre(THREAD* thread1, THREAD* thread2)
{
    string temp1;
    temp1 = "perdreSound";
    threadedPlay(thread1, temp1);
    
    char buffer[4];
    int i = random2(1,3);
    snprintf(buffer, 10, "%d", i);
    string temp2;
    temp2 = "perdre";
    temp2 = temp2+buffer;
    threadedPlay(thread2, temp2);
    return getFileDuration(temp1)+getFileDuration(temp2);
}
int Voice::playGagne(THREAD* thread1, THREAD* thread2)
{
    string temp1;
    temp1 = "gagneSound";
    threadedPlay(thread1, temp1);
    
    char buffer[4];
    int i = random2(1,3);
    snprintf(buffer, 10, "%d", i);
    string temp2;
    temp2 = "gagne";
    temp2 = temp2+buffer;
    threadedPlay(thread2, temp2);
    return getFileDuration(temp1)+getFileDuration(temp2);
}
int Voice::playPays(THREAD* thread, int numeroPays)
{
    char buffer1[4];
    int i = numeroPays;
    snprintf(buffer1, 10, "%d", i);
    
    char buffer2[4];
    i = random2(1,2);
    snprintf(buffer2, 10, "%d", i);
    
    string temp;
    temp = "pays";
    temp = temp+buffer1+buffer2;
    threadedPlay(thread, temp);
    
    return getFileDuration(temp);
}
int Voice::playAvance(THREAD* thread)
{
    char buffer[4];
    int i = random2(1,3);
    snprintf(buffer, 10, "%d", i);
    
    string temp;
    temp = "avance";
    temp = temp+buffer;
    threadedPlay(thread, temp);
    
    return getFileDuration(temp);
}
int Voice::playRecule(THREAD* thread)
{
    char buffer[4];
    int i = random2(1,3);
    snprintf(buffer, 10, "%d", i);
    
    string temp;
    temp = "recule";
    temp = temp+buffer;
    threadedPlay(thread, temp);
    
    return getFileDuration(temp);
}
int Voice::getFileDuration(string fileName)
{
    fileName = fileName + audioFileFormat;
    return int(info.duration[fileName]*1000);//-200);
}

