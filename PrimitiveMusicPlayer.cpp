#include <iostream>
#include <filesystem>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>
#include "functionen.hpp"
#pragma comment(lib, "Winmm.lib")
int main() {
	int enter{};
	std::vector<std::string> playlist;
	std::filesystem::path pathForMusic("Music");
	std::ofstream fileForSave{ "save.txt",std::ios::app };

	existsDirectory(pathForMusic);
	giveVecEntry(playlist, pathForMusic, fileForSave);

	while (1) {
		showPlaylist(playlist);
		//Switch is Coming soon for more options.
		playList(playlist);

		killInput();
		clear();
	}
	return EXIT_SUCCESS;
}

