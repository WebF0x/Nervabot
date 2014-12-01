/*
============================================================================
 Name : Armus.cpp
 Author : Equipe P4
 Description : Programme principal Nervabot
============================================================================
*/

#include "Robot.h"


using namespace std;


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
