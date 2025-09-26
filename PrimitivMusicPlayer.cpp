#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include "functionen.hpp"
int main(){
	//Brauche ich den file noch?
	//idee für Playlists, einen vector der dan vectoren spiecert jeder vector ist eine playlist. Eventuell dann auf files verzichten.
	int enter{};
	std::vector<std::string> playlist;
	std::filesystem::path pathForMusic("Music");
	std::ofstream fileForSave{ "save.txt",std::ios::app };

	existsDirectory(pathForMusic);
	giveVecEntry(playlist,pathForMusic,fileForSave);
	
	while (1) {
		showPlaylist(playlist);
		std::cout << "1. Play Music [COMING SOON!].\n2. Play the list." << std::endl;
		std::cin >> enter;
		if (std::cin.fail())
		{
			std::cerr << "Enter a number!" << std::endl;
			killInput();
			clear();
			continue;
		}
		else {
			switch (enter)
			{
				/*case 1:
					playMusic(playlist);
					break;
					*/
			case 2:
				killInput();
				playList(playlist);
				break;
			default: {
				std::cout << "No valid number." << std::endl;
				killInput();
				clear();
			}
			 break;
			}
		}
	}
	return EXIT_SUCCESS;
}
