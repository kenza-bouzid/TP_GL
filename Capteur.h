/*************************************************************************
                           ${Capteur}  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <Capteur> (fichier ${file_name}) ------
#if ! defined ( Capteur_H )
#define Capteur_H


//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
using namespace std;
#include "PorteeCapteur.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Rôle de la classe <Capteur>
//
//
//------------------------------------------------------------------------ 

class Capteur
{
//----------------------------------------------------------------- PUBLIC
    friend class Gestion;
public:
//----------------------------------------------------- Méthodes publiques
    int getCapteurId();
    string getDescription();
    PorteeCapteur getPortee();
    int getEtat();
    void definirPortee(long latitude, long longitude); 
//-------------------------------------------- Constructeurs - destructeur

    Capteur(int capteurid, string d, long lat, long lon);

    Capteur();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Capteur ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
//----------------------------------Attributs

    protected:
    int capteurId;
    string description;
    int etat;
    PorteeCapteur portee; 

 };

//----------------------------------------- Types dépendants de <Capteur>

#endif // Capteur_H
