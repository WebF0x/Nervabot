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
	Robot robot(true);
	AUDIO_SetVolume(100);

	THREAD thread, thread2;
	robot.voice.play(&thread,687);	//OK
	LCD_Printf("start playing");
    robot.voice.playQuestionRecette(&thread, &thread, 2);	//premier partie

    robot.voice.playGagne(&thread);	//playPerdre

    robot.voice.playReponseRecette(&thread,2);	//ok

    robot.voice.playQuestionRecette(&thread, &thread2, 5);	// pas joué

    robot.voice.playPerdre(&thread);	//pas joué

    robot.voice.playReponseRecette(&thread,5);	//pas joué
    pthread_join(thread, NULL);	//Wait until threads ends

    LCD_Printf("stop playing");
	/*
	AUDIO_SetVolume(100);
	AUDIO_PlayFile("audio.wav");
	THREAD_MSleep(10000);
	*/

	//robot.jeuRecette();
	//choixMenu(SERVO_325);

	return 0;
}
/*
//thread function prototype
void thread_capteurInfrarouge1();
void thread_capteurInfrarouge2();
int capteur1=0,capteur2=0;
int main()
{
 THREAD thread1,thread2;
 thread1 = THREAD_CreateSimple(thread_capteurInfrarouge1);
 thread2= THREAD_CreateSimple(thread_capteurInfrarouge2);
 //THREAD_Destroy(&thread1);

 while (1)
 {
	if (capteur1==1 && capteur2==1)
	{
		LCD_Printf("VRAI");
	}
 }

}

void thread_capteurInfrarouge1()
{
	while(1)
	{
		capteur1=capteurInfrarouge(1,260);
		THREAD_MSleep(500);
	}
}

void thread_capteurInfrarouge2()
{
	while(1)
	{
		capteur2=capteurInfrarouge(2,260);
		THREAD_MSleep(500);
	}
}
*/
