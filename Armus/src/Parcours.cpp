//#include "Parcours.h"
#include "Robot.h"

Parcours::Parcours():_pos(4), _r(NULL), _derniereReponse(true)
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
	if(_pos > 0 && _pos < 8)
	{
		if (reponsecourrante)
		{
			LCD_Printf("Le robot avance. Pos: %i\n", _pos);
			//avancerRobot();
		}
		else
		{
			LCD_Printf("Le robot recule. Pos: %i\n", _pos);
			//reculerRobot();
		}
		_derniereReponse = reponsecourrante;
	}
	else
	{
		LCD_Printf("Hors position\n");
	}
	LCD_Printf("position:%i\n", _pos);
}

void Parcours::avancerRobot()
{
	//if(_pos != 4)
	//{
		if(_derniereReponse == false)
		{
			_r->tournerSurPlace(184);
		}
		_r->avancer(35);
	/*}
	else
	{
		if(_derniereReponse == true)
		{
			_r->tournerSurPlace(92);
		}
		else
		{
			_r->tournerSurPlace(184);
		}
		_r->avancer(50);
	}*/
	_pos++;


}

void Parcours::reculerRobot()
{
	//if(_pos != 4)
	//{
		if(_derniereReponse == true)
		{
			_r->tournerSurPlace(184);
		}
		_r->avancer(50);
	/*}
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
	}*/
	_pos--;
}
