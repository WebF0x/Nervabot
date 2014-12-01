//#include "Parcours.h"
#include "Robot.h"

Parcours::Parcours():_pos(3), _r(NULL), _derniereReponse(true)
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
	if(_pos > 1 && _pos <=7)
	{
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
	else
	{
		LCD_Printf("Hors position\n");
	}
}

void Parcours::avancerRobot()
{
	if(_pos != 4)
	{
		if(_derniereReponse == false)
		{
			_r->tournerSurPlace(184);
		}
		_r->avancer(50);
	}
	else
	{
		if(_derniereReponse == true)
		{
			_r->tournerSurPlace(91);
		}
		else
		{
			_r->tournerSurPlace(184);
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
			_r->tournerSurPlace(184);
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
			_r->tournerSurPlace(184);
		}
		_r->avancer(50);
	}
	_pos--;
}
