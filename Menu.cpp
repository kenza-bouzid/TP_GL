/*************************************************************************
                           Menu 
                             -------------------
	début                : 04/06/2019
	copyright            : (C) 2019 par BOUZID Kenza    - JEANNE Nathan
										HAMIDOVIC David - CAVAGNA Margaux
*************************************************************************/

//---------- Réalisation de la classe <Menu> (fichier ${file_name}) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
//------------------------------------------------------ Include personnel
#include "Menu.h"
#include "Gestion.h"
#include "Etude.h"
#include "Catalogue.h"
#include "Seuil.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Menu::run()
{
	string inputLine = "";

	do
	{
		// Lecture de la commande utlisateur 
		cout << ">";
		//cin >> inputLine;
		getline(cin, inputLine);

		//Traitement de la commande 
		if(!traitement(inputLine)) 
			cout << "commande inexistante, tapez 'help' pour la liste des commandes" << endl;

	} while (inputLine.compare("exit"));
	
}

void Menu::init()
{
	Lecture l;
	l.InitSeuils(tabSeuils, "../Fichiers/Seuils.csv");
	l.InitCapteur(listeCapteurs, "../Fichiers/capteurComplet.csv");
	l.InitTypeGaz("../Fichiers/gazTest.csv");

	l.Parcourir(c, "../Fichiers/fichier1000.csv");
}



//-------------------------------------------- Constructeurs - destructeur

Menu::Menu()
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur de <Menu>" << endl;
#endif

	c = new Catalogue();

} //----- Fin de Menu

Menu::~Menu()
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de <Menu>" << endl;
#endif
	delete c;
} //----- Fin de ~Menu

//------------------------------------------------------------------ PRIVE

//------------------------------------------------------- Méthodes privées


bool Menu::traitement(string input)
{	
	vector<string> argList; //Liste des arguments passés dans la commande (les -s)
	unordered_map<string,string> valueList; //Liste des valeurs des paramètres passés dans la commande (les -r=X)

	split(argList, valueList, input);


	if (argList.empty()) return true;

	if (commande(argList, "exit")) return true;


	if(commande(argList, "atmo")) //------------------------------------- Etude de l'ATMO
	{
		// On a toujours -lat= et -long= 
		// La date si elle n'est pas mise est celle d'hier
		// Param a mettre -r -d si date et rayon, sinon que latitude et longitude 
		// -dateF=  pour date de fin & -dateD= pour date début
		// Format de date : YYYY-MM-DDTHH:MM:SS.SSSSSSSS
		// -s si valeurs a afficher
		
		long double lat = atof(valueList.find("-lat")->second.c_str());
		long double lon = atof(valueList.find("-long")->second.c_str());;
		
		double rayon = commande(argList, "-r") ? atof(valueList.find("-r")->second.c_str()) : 2000;
		
		Date dateD;
		Date dateF;
		dateF = commande(argList, "-d") ? Date(valueList.find("-dateF")->second.c_str()) : dateF.precedent();
		dateD = commande(argList, "-d") ? Date(valueList.find("-dateD")->second.c_str()) : dateF.now();
			
		if (commande(argList, "-s"))
		{
			//TODO : Affichage valeurs mesure
			//e.Evaluer(c, listeCapteurs, lat, lon, dateD, dateF);
		}
		else
		{
			//TODO : Affichage ATMO
			//vector<ConcentrationIndice> mesures = e.Evaluer(c, listeCapteurs, lat, lon, dateD, dateF);
			//cout << "[atmo] " << e.CalculAtmo(mesures, tabSeuils) << endl;
		}
	}


	if (commande(argList, "stats")) //----------------------------------- Etude des statistiques
	{
		// Commande de la forme : stats -n=3 pour l'etude de 3 capteurs

		int n = atoi(valueList.find("-n")->second.c_str());
		//e.DetecterCapteursSimilaires(*c, n);
		//TODO : appel et affichage capteurs similaires

	}

	if (commande(argList, "sensor")) //---------------------------------- Gestion des capteurs
	{
		if (commande(argList, "add"))
		{
			long double lat = atof(valueList.find("-lat")->second.c_str());
			long double lon = atof(valueList.find("-long")->second.c_str());;
			string description = valueList.find("-d")->second;
			int cId = atoi(valueList.find("-id")->second.c_str());

			Capteur c(cId, description, lat, lon);
			g.AjouterCapteur(c, listeCapteurs);
		}

		if (commande(argList, "remove"))		
		{
			int cId = atoi(valueList.find("-id")->second.c_str());
			g.SupprimerCapteur(cId, listeCapteurs);
		}

		if (commande(argList, "exclude"))
		{
			int cId = atoi(valueList.find("-id")->second.c_str());
			g.MettreEnVeilleCapteur(cId, listeCapteurs);
		}

		if (commande(argList, "include"))
		{
			int cId = atoi(valueList.find("-id")->second.c_str());
			g.RestaurerCapteur(cId, listeCapteurs);
		}
	}

	if (commande(argList, "seuil")) //----------------------------------- Gestion du seuil
	{
		if (commande(argList, "print"))
		{
			cout << "[seuils]" << "\n" << endl;
			AfficherSeuils(tabSeuils);
		}
		else
		{
			int gazId = l.getGazName()[valueList.find("-gazId")->second];
			int min = atoi(valueList.find("-min")->second.c_str());
			int max = atoi(valueList.find("-max")->second.c_str());
			int indice = atoi(valueList.find("-indice")->second.c_str());

			Seuil s(min, max, indice);

			g.ChangerUnSeuil(tabSeuils, gazId, s);
		}
	}

}

void Menu::AfficherSeuils(unordered_map<int, vector<Seuil>> &umap)
{
	cout << "Indice   |   SO2   |   NO2  |   O3   |   PM   |" << endl;

	auto itPM10 = umap[PM10].rbegin();
	auto itSO2 = umap[SO2].rbegin();
	auto itNO2 = umap[NO2].rbegin();
	auto itO3 = umap[O3].rbegin();

	for (int i = 10; i >= 1; i--)
	{
		cout << i << "        |   " << itSO2->getMin() << "-" << itSO2->getMax() << "   |   "
			<< itNO2->getMin() << "-" << itNO2->getMax() << "   |   "
			<< itO3->getMin() << "-" << itO3->getMax() << "   |   "
			<< itPM10->getMin() << "-" << itPM10->getMax() << "   |   " << endl;
		++itPM10;
		++itSO2;
		++itNO2;
		++itO3;

	}
}

bool Menu::commande(vector<string> c, string s) 
{
	return find(c.begin(), c.end(), s) != c.end();
}

void Menu::split(vector<string> &argList, unordered_map<string, string> &valueList, string s)
{

	string delimiter = " ";
	size_t pos = 0;
	string token;
	char prefix = '-';

	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);

		if (token[0] == prefix) //si forme -a ou -aa=555
		{
			size_t pos1 = token.find("=");

			if (pos1 != std::string::npos) // forme -a=66
			{
				string t = token.substr(0, pos1);
				token.erase(0, pos1 + delimiter.length());
				argList.push_back(t);
				valueList.emplace(make_pair(t, token));
			}
			else {
				argList.push_back(token);
			}
		}
		else {
			argList.push_back(token);
		}

		s.erase(0, pos + delimiter.length());
	}
	if (s[0] == prefix) //si forme -a ou -aa=555
	{
		size_t pos1 = s.find("=");

		if (pos1 != std::string::npos) // forme -a=66
		{
			string t = s.substr(0, pos1);
			s.erase(0, pos1 + delimiter.length());
			argList.push_back(t);
			valueList.emplace(make_pair(t, s));
		}
		else {
			argList.push_back(s);
		}
	}
	else {
		argList.push_back(s);
	}
}
void Menu::afficheMatSimilarite(bool**matSimilarite, string gaz, double precision) {
	cout << "Matrices de similarite des capteurs pour le gaz " << gaz << "  avec un ecart tolere de: " << precision << endl << endl;
	cout << "     |";
	for (int i = 0; i < 10; i++)
	{
		cout << i << "    |";
	}
	cout << endl;
	cout << "------------------------------------------------------------------" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << "    |";
		for (int j = 0; j < 10; j++)
		{
			cout << matSimilarite[i][j] << "    |";
		}
		cout << endl;
	}
	cout << endl;
}
void Menu::afficheMatMoyenne(unordered_map<int, vector<long double> >moyenneCapteur) {
	cout << "Moyennes des messures de capteurs par gaz" << endl;
	cout << "Capteur n |    O3    |   PM10   |    SO2    |    NO2    |" << endl;
	cout << "---------------------------------------------------------" << endl;
	for (auto x : moyenneCapteur)
	{
		cout << x.first << "         |" <<
			x.second[O3] << "   | " <<
			x.second[PM10] << "  | " <<
			x.second[SO2] << "   | " <<
			x.second[NO2] << "   | " << endl;
	}
	cout << endl;
}
void Menu::afficheMatEcart(string gaz, long double** matriceEcartGaz, int nbCapteurs ) {

	cout << "Matrices des ecarts de mesures capteurs pour le gaz " << gaz << endl << endl;
	cout << "    |";
	for (int i = 0; i < nbCapteurs; i++)
	{
		cout << i << "      |";
	}
	cout << endl;
	cout << "-------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < nbCapteurs; i++)
	{
		cout << i << "   |";
		for (int j = 0; j < nbCapteurs; j++)
		{

			if (i == j)
			{
				cout << matriceEcartGaz[i][j] << "      |";
			}
			else
			{
				cout << matriceEcartGaz[i][j] << '|';
			}
		}
		cout << endl;
	}
	cout << endl;
}

void Menu::afficherSousIndiceAtmo(vector<ConcentrationIndice> listeConcIndice)
{
	int atmo = e.CalculAtmo(listeConcIndice);
	if (atmo != 0)
	{
		cout << "PM10: " << listeConcIndice[PM10];
		cout << "SO2: " << listeConcIndice[SO2];
		cout << "NO2: " << listeConcIndice[NO2];
		cout << "O3: " << listeConcIndice[O3];
	}
}
