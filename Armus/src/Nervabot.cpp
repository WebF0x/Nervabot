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
	Robot robot;
    Voice voice;
    
    SYSTEM_ResetTimer();
    
    while (true)
	{
		
		if (DIGITALIO_Read(BMP_RIGHT))
		{
			break;
		}
        
	}
    float temps = SYSTEM_ReadTimerMSeconds()/1000;
    LCD_Printf("Temps: %f\n", temps);
    
    
    THREAD t1, t2, t3;
    voice.playTempsPartie(&t1, &t2, &t3, temps);
    pthread_join(t3, NULL);
    voice.playTempsQuestion(&t1, &t2, &t3, temps+10);
    pthread_join(t3, NULL);
    
	return 0;
}
