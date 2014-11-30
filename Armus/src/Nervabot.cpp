/*
============================================================================
 Name : Armus.cpp
 Author : Equipe P4
 Description : Programme principal Nervabot
============================================================================
*/

#include "Robot.h"

using namespace std;

int main()
{
	Robot bob(true);

	THREAD t1,t2;

	bob.threadedSay(&t1, 6);	//Create and start threads
	bob.threadedSay(&t2, "Allo");

	pthread_join(t1, NULL);	//Wait until threads ends
	pthread_join(t2, NULL);

	return 0;
}
