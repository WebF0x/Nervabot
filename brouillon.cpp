#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

enum Viande
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

class Recette
{
public:
    Recette(string nom, Viande viande,LegumeFruit legumeFruit,Laitier laitier,Cerealier cerealier,GroupeAlimentaire groupeManquant)
    {
        this->nom = nom;
        this->viande = viande;
        this->legumeFruit = legumeFruit;
        this->laitier = laitier;
        this->cerealier = cerealier;

        this->groupeManquant = groupeManquant;
    }

    std::string nom;
    Viande viande;
    LegumeFruit legumeFruit;
    Laitier laitier;
    Cerealier cerealier;

    GroupeAlimentaire groupeManquant;
};

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
    cout<<recette.nom<<":\t";
    if(recette.groupeManquant != VIANDE)        cout<<toString(recette.viande)<<'\t';
    if(recette.groupeManquant != LEGUME_FRUIT)  cout<<toString(recette.legumeFruit)<<'\t';
    if(recette.groupeManquant != LAITIER)       cout<<toString(recette.laitier)<<'\t';
    if(recette.groupeManquant != CEREALIER)     cout<<toString(recette.cerealier)<<'\t';

    cout<<endl;
}

bool demanderGroupeAlimentaire(GroupeAlimentaire groupe)
{
    cout<<VIANDE<<": "<<toString(VIANDE)<<endl;
    cout<<LEGUME_FRUIT<<": "<<toString(LEGUME_FRUIT)<<endl;
    cout<<LAITIER<<": "<<toString(LAITIER)<<endl;
    cout<<CEREALIER<<": "<<toString(CEREALIER)<<endl;

    int choix;
    cin>>choix;

    return (choix==groupe);
}

bool demanderAliment(GroupeAlimentaire groupe)
{
    cout<<VIANDE<<": "<<exempleAliment(VIANDE)<<endl;
    cout<<LEGUME_FRUIT<<": "<<exempleAliment(LEGUME_FRUIT)<<endl;
    cout<<LAITIER<<": "<<exempleAliment(LAITIER)<<endl;
    cout<<CEREALIER<<": "<<exempleAliment(CEREALIER)<<endl;

    int choix;
    cin>>choix;

    return (choix==groupe);
}

int main()
{
    //Hasard
    srand (time(NULL));

    //Definir les recettes
    vector<Recette> recettes =
    {
        {"Hamburger", POULET, LAITUE, FROMAGE, PAIN, VIANDE},
        {"Hamburger", POULET, LAITUE, FROMAGE, PAIN, CEREALIER},

        {"Hamburger", POULET, TOMATE, FROMAGE, PAIN, VIANDE},
        {"Hamburger", POULET, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT},
        {"Hamburger", POULET, TOMATE, FROMAGE, PAIN, CEREALIER},

        {"Hamburger", BOEUF, LAITUE, FROMAGE, PAIN, CEREALIER},

        {"Hamburger", BOEUF, TOMATE, FROMAGE, PAIN, LEGUME_FRUIT},
        {"Hamburger", BOEUF, TOMATE, FROMAGE, PAIN, CEREALIER}
    };

    //Selectionner une recette au hasard
    int numeroDeRecette = rand() % recettes.size();
    Recette& recette = recettes.at(numeroDeRecette);

    //Afficher la recette
    afficherRecette(recette);

    //Demander groupe alimentaire manquant
    cout<<"Il manque un groupe alimentaire. Lequel?"<<endl;
    bool bonneReponse = demanderGroupeAlimentaire(recette.groupeManquant);

    if(bonneReponse)    cout<<"Bravo!"<<endl;
    else                cout<<"Faux!"<<endl;

    cout<<"Le groupe manquant est: "<<toString(recette.groupeManquant)<<endl;

    //Demander un aliment de ce groupe
    cout<<"Quel aliment fait partie des "<<toString(recette.groupeManquant)<<endl;
    bonneReponse = demanderAliment(recette.groupeManquant);

    if(bonneReponse)    cout<<"Bravo!"<<endl;
    else                cout<<"Faux!"<<endl;

    cout<<"La bonne reponse est "<<exempleAliment(recette.groupeManquant)<<endl;

    return 0;
}
