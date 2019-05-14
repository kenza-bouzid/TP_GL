/*************************************************************************
                           Etude  -  description
                             -------------------
    début                : ${date}
    copyright            : (C) ${year} par ${user}
*************************************************************************/

//---------- Interface de la classe <Etude> (fichier ${file_name}) ------
#if ! defined (ETUDE_H)
#define ETUDE_H

//--------------------------------------------------- Interfaces utilisées
#include <vector>
#include <math.h>
#include "Date.h"
#include "Capteur.h"
#include "PorteeCapteur.h"


//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Etude>
//
//
//------------------------------------------------------------------------

class Etude 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste de paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void Evaluer (double latitude, double longitude, Date dateF, Date dateD, double rayon = 0 ); 
    vector<Capteur> getCapteur( vector<Capteur>listCapteur,double latitude, double longitude ,double rayon = 0 ); 

//------------------------------------------------- Surcharge d'opérateurs
    Etude & operator = ( const Etude & unEtude );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Etude ( const Etude & unEtude );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Etude ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Etude ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Etude>

#endif // Etude