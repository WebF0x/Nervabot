/*
 * Recette.cpp
 *
 *  Created on: 2014-11-20
 *      Author: Maxime
 */

#include "Recette.h"

using namespace std;

Recette::Recette(string nom,
    		Viande viande,LegumeFruit legumeFruit,Laitier laitier,Cerealier cerealier,
    		GroupeAlimentaire groupeManquant)
{
	this->nom = nom;
	this->viande = viande;
	this->legumeFruit = legumeFruit;
	this->laitier = laitier;
	this->cerealier = cerealier;

	this->groupeManquant = groupeManquant;
}

string toString(Viande aliment)
{
    switch(aliment)
    {
        case POULET:    return "poulet";
        case BOEUF:     return "boeuf";
        case OEUF:      return "oeuf";
        case SAUCISSE:  return "saucisse";
        case JAMBON:    return "jambon";
        case BACON:     return "bacon";

        default:        return "Inconnu";
    }
}

string toString(LegumeFruit aliment)
{
    switch(aliment)
    {
        case TOMATE:    return "tomate";
        case LAITUE:     return "laitue";
        case FRAISE:      return "fraisee";
        case CAROTTE:    return "carotte";
        case ORANGE:     return "orange";

        default:        return "Inconnu";
    }
}

string toString(Laitier aliment)
{
    switch(aliment)
    {
        case LAIT:    return "lait";
        case FROMAGE:     return "fromage";
        case YOGOURT:      return "yogourt";

        default:        return "Inconnu";
    }
}

string toString(Cerealier aliment)
{
    switch(aliment)
    {
        case PAIN:    return "pain";
        case CREPE:     return "crepe";
        case FARINE:      return "farine";
        case PATES:  return "pates";

        default:        return "Inconnu";
    }
}

string toString(GroupeAlimentaire aliment)
{
    switch(aliment)
    {
        case VIANDE:        return "viandes et substituts";
        case LEGUME_FRUIT:  return "legumes et fruits";
        case LAITIER:       return "produits laitiers";
        case CEREALIER:     return "produits cerealiers";

        default:            return "Inconnu";
    }
}

string exempleAliment(GroupeAlimentaire aliment)
{
    switch(aliment)
    {
        case VIANDE:        return "le poulet";
        case LEGUME_FRUIT:  return "la tomate";
        case LAITIER:       return "le lait";
        case CEREALIER:     return "le pain";

        default:            return "Inconnu";
    }
}

void afficherRecette(const Recette& recette)
{
    LCD_Printf("%s: ", recette.nom.data());
    if(recette.groupeManquant != VIANDE)        LCD_Printf("%s ", toString(recette.viande).data());
    if(recette.groupeManquant != LEGUME_FRUIT)  LCD_Printf("%s ", toString(recette.legumeFruit).data());
    if(recette.groupeManquant != LAITIER)       LCD_Printf("%s ", toString(recette.laitier).data());
    if(recette.groupeManquant != CEREALIER)     LCD_Printf("%s ", toString(recette.cerealier).data());

    LCD_Printf("\n");
}


