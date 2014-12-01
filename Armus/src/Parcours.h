#ifndef PARCOURS_H_
#define PARCOURS_H_

class Parcours
{
	unsigned char _pos;
public:
	Parcours();
	Parcours(unsigned char pos);
	void deplacer(bool bonnereponse);
};

#endif /* PARCOURS_H_ */
