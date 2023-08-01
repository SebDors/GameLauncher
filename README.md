
# Game Launcher with Mouse Settings Changer

This C++ program is a game launcher that allows you to choose and launch different games. Additionally, it includes a feature to change the mouse settings based on the selected game. The program reads the game choice from a Notepad file and performs actions accordingly.

## Requirements

* Windows operating system
* C++ compiler (supporting C++17)
* Mouse settings file path: "C:\Users\dorss\OneDrive\Bureau\Jeux\Souris_Choose.txt"

## How to Use

1. Compile the program using a C++ compiler with C++17 support.
2. Run the compiled executable in the same directory as the `Games` and `Applications_Tiers` folders.
3. Choose a game to launch by entering the corresponding number.
4. If you choose to launch League of Legends, it will also start "Porofessor.gg" in the background.
5. If you choose to quit the League of Legends game, it will terminate "LeagueClient.exe" and "Overwolf.exe".
6. The program will check the "Souris_Choose.txt" file and change the mouse settings accordingly.

**Note:** Make sure to set up the proper file paths for your games and applications.

## File Structure

- Games: Directory containing shortcuts to various games.
- Applications_Tiers: Directory containing shortcuts to third-party applications.
- Souris_Choose.txt: Notepad file to store the mouse settings.

## How to Add Games

1. Create a shortcut (.lnk) to the game executable or its launcher and place it in the `Games` folder.
2. The program will automatically detect and list all the available games.

## How to Add Third-Party Applications

1. Create a shortcut (.lnk) to the application executable and place it in the `Applications_Tiers` folder.
2. When you launch a specific game (e.g., League of Legends), the program will automatically start the associated third-party application.

## Important Notes

* Make sure to provide the correct paths for the `MouseSettingPath` and `pathToStart` variables to work with your system.
* Adjust the paths inside the functions `ChangeNumber`, `CheckChanges`, `EnumerateFile`, and `main` as needed.

**Disclaimer:** This program is intended for educational purposes only and may require modifications to work correctly on your system. Use it at your own risk.

**For any questions or assistance with the program, please feel free to reach out. Happy gaming!**
