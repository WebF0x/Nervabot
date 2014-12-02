/*
 * Recette.h
 *
 *  Created on: 2014-11-20
 *      Author: Maxime
 */

#ifndef RECETTE_H_
#define RECETTE_H_

#include <string>
#include <vector>

#include <libarmus.h> 	//LCD_Printf

typedef enum Viande
{
    POULET,
    BOEUF,
    OEUF,
    SAUCISSE,
    JAMBON,
    BACON
};

enum LegumeFruit
{
    TOMATE,
    LAITUE,
    FRAISE,
    CAROTTE,
    ORANGE
};

enum Laitier
{
    LAIT,
    FROMAGE,
    YOGOURT
};

enum Cerealier
{
    PAIN,
    CREPE,
    FARINE,
    PATES
};

enum GroupeAlimentaire
{
    VIANDE,
    LEGUME_FRUIT,
    LAITIER,
    CEREALIER
};

std::string toString(Viande aliment);
std::string toString(LegumeFruit aliment);
std::string toString(Laitier aliment);
std::string toString(Cerealier aliment);
std::string toString(GroupeAlimentaire aliment);
std::string exempleAliment(GroupeAlimentaire aliment);

class Recette
{
public:
    Recette(std::string nom,
    		Viande viande,LegumeFruit legumeFruit,Laitier laitier,Cerealier cerealier,
    		GroupeAlimentaire groupeManquant);

    std::string nom;
    Viande viande;
    LegumeFruit legumeFruit;
    Laitier laitier;
    Cerealier cerealier;

    GroupeAlimentaire groupeManquant;
};

void afficherRecette(const Recette& recette);

#endif /* RECETTE_H_ */
