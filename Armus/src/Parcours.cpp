//#include "Parcours.h"
#include "Robot.h"

Parcours::Parcours():_pos(1), _r(NULL), _derniereReponse(true)
{
}

Parcours::Parcours(unsigned int pos): _pos(pos), _r(NULL), _derniereReponse(true)
{
}

unsigned int Parcours::getPosition()
{
	return _pos;
}

void Parcours::initRobot(Robot* r)
{
	_r = r;
}

void Parcours::deplacer(bool reponsecourrante)
{
	LCD_Printf("position:%i\n", _pos);
	//LCD_Printf("reponse courante:%i\n", reponsecourrante);
	//LCD_Printf("derniere reponse:%i\n", _derniereReponse);
	if (reponsecourrante)
	{
		avancerRobot();
	}
	else
	{
		reculerRobot();
	}
	_derniereReponse = reponsecourrante;
}

void Parcours::avancerRobot()
{
	if(_pos != 4)
	{
		if(_derniereReponse == false)
		{
			_r->tournerSurPlace(180);
		}
		_r->avancer(50);
	}
	else
	{
		if(_derniereReponse == true)
		{
			_r->tournerSurPlace(90);
		}
		else
		{
			_r->tournerSurPlace(180);
		}
		_r->avancer(50);
	}
	_pos++;


}

void Parcours::reculerRobot()
{
	if(_pos != 4)
	{
		if(_derniereReponse == true)
		{
			_r->tournerSurPlace(180);
		}
		_r->avancer(50);
	}
	else
	{
		if(_derniereReponse == false)
		{
			_r->tournerSurPlace(-90);
		}
		else
		{
			_r->tournerSurPlace(180);
		}
		_r->avancer(50);
	}
	_pos--;
}
