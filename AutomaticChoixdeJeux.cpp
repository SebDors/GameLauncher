#include "iostream"
using namespace std;
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include "unistd.h"
string MousePath = "C:\\Users\\dorss\\OneDrive\\Bureau\\Jeux\\Souris_Choose.txt";
int choix;                // Choix du jeu à lancer
bool LOL = false;         // Savoir si LoL est lancé ou non
bool Needchange = false;  // Doit-on changer la valeur du bloc-note
vector<string> filePaths; // Tableau pour stocker les chemins des fichiers

void ChangeNumber(string &ChiffreInBlocNote)
{
    // Si il y a besoin de changer le chiffre
    if (Needchange)
    {
        ofstream myfile("C:\\Users\\dorss\\OneDrive\\Bureau\\Jeux\\Souris_Choose.txt");
        // Fichier à ouvrir
        if (myfile.is_open() && ChiffreInBlocNote == "1")
        {
            myfile << "2"; // Changer par 2
            myfile.close();
        }
        if (myfile.is_open() && ChiffreInBlocNote == "2")
        {
            myfile << "1"; // Changer par 1
            myfile.close();
        }
        cout << "Changer les parametres de la souris";
        sleep(5);                                    // Wait to change settings
        system("taskkill /f /im OemDrv.exe 1>NULL"); // Shutdown Mouse's program
    }
}

void CheckChanges()
{
    ifstream myfile(MousePath); // Fichier à ouvrir
    string NotePadChoose;       // Variable contenant la valeur dans le bloc note
    if (myfile.is_open())
    {
        while (getline(myfile, NotePadChoose))
        {
            cout << "Dans le Notepad : " << NotePadChoose << '\n';
        }
        if (NotePadChoose == "2" && LOL == true)
        {
            system("start C:\\Users\\dorss\\OneDrive\\Bureau\\T21_Wired_Gaming_Mouse.lnk");
            cout << "J'ouvre T21" << endl;
            Needchange = true;
        }
        else if (NotePadChoose == "1" && LOL == false)
        {
            system("start C:\\Users\\dorss\\OneDrive\\Bureau\\T21_Wired_Gaming_Mouse.lnk");
            cout << "J'ouvre T21" << endl;
            Needchange = true;
        }
        myfile.close();
    }
    ChangeNumber(NotePadChoose);
}

void EnumerateFile()
{
    string path = "Jeux";

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        string filePath = entry.path().string();
        filePaths.push_back(filePath);
    }
}

void EnumerateGames()
{
    string ListeJeux = R"(

 ______     ______     __    __     ______     ______
/\  ___\   /\  __ \   /\ "-./  \   /\  ___\   /\  ___\
\ \ \__ \  \ \  __ \  \ \ \-./\ \  \ \  __\   \ \___  \
 \ \_____\  \ \_\ \_\  \ \_\ \ \_\  \ \_____\  \/\_____\
  \/_____/   \/_/\/_/   \/_/  \/_/   \/_____/   \/_____/


Quel jeux lancer :
    0 - Quit League Of Legends
)";
    // Parcourir tous les fichiers
    for (int i = 0; i < filePaths.size(); i++)
    {
        filePaths[i].erase(0, 5);                                                  // Se mettre à la première position pour supprimer "/Jeux"
        filePaths[i].erase((filePaths[i].size() - 4), 4);                          // Supprimer ".lnk" à la fin du raccourci
        ListeJeux += "    " + std::to_string(i + 1) + " - " + filePaths[i] + "\n"; // Intégrer dans ListeJeux tout les jeux
    }
    cout << ListeJeux;
}

int main()
{
    EnumerateFile();  // Trouver les fichiers
    EnumerateGames(); // Ecrire les jeux

    while (true)
    {
        cin >> choix; // Récupérer le chiffre

        if (choix > filePaths.size())
        {
            cout << "mauvaise entree, reessayer" << endl;
            continue; // Restart the loop to get a valid input
        }
        else if (choix != 0)
        {
            choix--;
            string pathToStart = "start Jeux/" + filePaths[choix] + ".lnk";
            system(pathToStart.c_str());
            LOL = false;
            if (filePaths[choix] == "League_of_Legends")
            {
                LOL = true;
                system("start Applications_Tiers/Porofessor.gg.lnk");
            }

            break;
        }
        else
        {
            // Fermer les logiciels
            system("taskkill /f /im LeagueClient.exe 1>NULL");
            system("taskkill /f /im Overwolf.exe 1>NULL");
            LOL = false;
            break; // Exit the loop and continue with the rest of the code
        }
    }
    CheckChanges();
}
