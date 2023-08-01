#include "iostream"
using namespace std;
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include "unistd.h"

string MouseSettingPath = "C:\\Users\\dorss\\OneDrive\\Bureau\\Jeux\\Souris_Choose.txt";
int choix;                // Choice of the game to launch
bool LOL = false;         // Check if LoL (League of Legends) is running or not
bool Needchange = false;  // Should we change the value in the Notepad file?
vector<string> filePaths; // Array to store file paths

// Function to change the number in the Notepad file
void ChangeNumber(string &ChiffreInBlocNote)
{
    // If there is a need to change the number
    if (Needchange)
    {
        ofstream myfile(MouseSettingPath);
        // Open the file
        if (myfile.is_open() && ChiffreInBlocNote == "1")
        {
            myfile << "2"; // Change to 2
            myfile.close();
        }
        if (myfile.is_open() && ChiffreInBlocNote == "2")
        {
            myfile << "1"; // Change to 1
            myfile.close();
        }
        cout << "Changing mouse settings";
        sleep(5);                                    // Wait to change settings
        system("taskkill /f /im OemDrv.exe 1>NULL"); // Shutdown Mouse's program
    }
}

// Function to check for changes in the Notepad file and act accordingly
void CheckChanges()
{
    ifstream myfile(MouseSettingPath); // Open the file
    string NotePadChoose;       // Variable containing the value in the Notepad file
    if (myfile.is_open())
    {
        while (getline(myfile, NotePadChoose))
        {
            cout << "In the Notepad: " << NotePadChoose << '\n';
        }
        if (NotePadChoose == "2" && LOL == true)
        {
            system("start C:\\Users\\dorss\\OneDrive\\Bureau\\T21_Wired_Gaming_Mouse.lnk");
            cout << "Opening T21" << endl;
            Needchange = true;
        }
        else if (NotePadChoose == "1" && LOL == false)
        {
            system("start C:\\Users\\dorss\\OneDrive\\Bureau\\T21_Wired_Gaming_Mouse.lnk");
            cout << "Opening T21" << endl;
            Needchange = true;
        }
        myfile.close();
    }
    ChangeNumber(NotePadChoose);
}

// Function to enumerate files in a directory and store their paths in the vector
void EnumerateFile()
{
    string path = "Games";

    for (const auto &entry : std::filesystem::directory_iterator(path))
    {
        string filePath = entry.path().string();
        filePaths.push_back(filePath);
    }
}

// Function to enumerate available games and display them with indices
void EnumerateGames()
{
    string ListeJeux = R"(

 ______     ______     __    __     ______     ______
/\  ___\   /\  __ \   /\ "-./  \   /\  ___\   /\  ___\
\ \ \__ \  \ \  __ \  \ \ \-./\ \  \ \  __\   \ \___  \
 \ \_____\  \ \_\ \_\  \ \_\ \ \_\  \ \_____\  \/\_____\
  \/_____/   \/_/\/_/   \/_/  \/_/   \/_____/   \/_____/


Which game to launch:
    0 - Quit League Of Legends
)";
    // Browse all the files
    for (int i = 0; i < filePaths.size(); i++)
    {
        filePaths[i].erase(0, 6);                                                  // Move to the first position to remove "/Jeux"
        filePaths[i].erase((filePaths[i].size() - 4), 4);                          // Remove ".lnk" at the end of the shortcut
        ListeJeux += "    " + std::to_string(i + 1) + " - " + filePaths[i] + "\n"; // Add all the games to ListeJeux
    }
    cout << ListeJeux;
}

int main()
{
    EnumerateFile();  // Find files
    EnumerateGames(); // List games

    while (true)
    {
        cin >> choix; // Get the number

        if (choix > filePaths.size())
        {
            cout << "Invalid input, please try again" << endl;
            continue; // Restart the loop to get a valid input
        }
        else if (choix != 0)
        {
            choix--;
            string pathToStart = "start Games/" + filePaths[choix] + ".lnk";
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
            // Close the software
            system("taskkill /f /im LeagueClient.exe 1>NULL");
            system("taskkill /f /im Overwolf.exe 1>NULL");
            LOL = false;
            break; // Exit the loop and continue with the rest of the code
        }
    }
    CheckChanges();
}
