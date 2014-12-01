//#include "Parcours.h"
#include "Robot.h"

Parcours::Parcours():_pos(3), _r(NULL), _derniereReponse(true)
{
}

Parcours::Parcours(unsigned char pos): _pos(pos), _r(NULL), _derniereReponse(true)
{
}

void Parcours::initRobot(Robot* r)
{
	_r = r;
}

void Parcours::deplacer(bool bonnereponse)
{
	if (bonnereponse)
	{
		avancerRobot();
	}
	else
	{
		reculerRobot();
	}
	_derniereReponse = bonnereponse;
}

void Parcours::avancerRobot()
{
	if(_pos != 4)
	{
		if(!_derniereReponse == false)
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
