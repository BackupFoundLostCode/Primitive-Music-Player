#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include "functionen.hpp"
int main(){
	int enter{};
	std::vector<std::string> playlist;
	std::filesystem::path pathForMusic("Music");
	std::ofstream fileForSave{ "save.txt",std::ios::app };

	existsDirectory(pathForMusic);
	giveVecEntry(playlist);
	
	while (1) {
		showPlaylist(playlist);
		std::cout << "1. Musik spielen.\n2. Neuer Song in die Liste:" << std::endl;

		std::cin >> enter;
		if (std::cin.fail())
		{
			std::cerr << "Eine Nummer eingeben!" << std::endl;
			killInput();
			continue;
		}
		switch (enter)
		{
		case 2:
			killInput();
			addSong(playlist, fileForSave);
			break;
		case 1: 
			playMusic(playlist);
			break;
		default:
			break;
		}
	}
	return EXIT_SUCCESS;
}
