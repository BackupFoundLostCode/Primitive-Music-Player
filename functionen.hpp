#pragma once
#include <iostream>
#include <filesystem>
#include <fstream> 
#include <Windows.h>
void killInput() {
	std::cin.clear();
	std::cin.ignore(50, '\n');
}
void clear() {
	system("pause");
	system("cls");
}
void existsDirectory(const std::filesystem::path& pathForMusic) {
	if (std::filesystem::create_directory(pathForMusic))
	{
		std::cout << "Ordner Erstellt!\n" << std::endl;
	}
	else
	{
		std::cerr << "Ordner Konnte nicht erstellt werden oder existiert beriets.\n" << std::endl;
	}
}
void giveVecEntry(std::vector<std::string>& playlist, const std::filesystem::path& pathForMusic, std::ofstream& fileForSave)
{
	for (const auto& s : std::filesystem::directory_iterator(pathForMusic))
	{
		auto filename = s.path().filename().string();
		playlist.push_back(filename);
	}
}
void showPlaylist(const std::vector<std::string>& playlist) {
	std::cout << "Title: " << "\n"<<std::endl;
	for (size_t i = 0; i < playlist.size(); i++)
	{
		std::cout <<"["<<i<<"]"<< playlist[i] << std::endl;
	}
	std::cout << "\n";
}
void playMusic(const std::vector<std::string>& playlist) {
	int song{};
	int ii{};
	bool makeEntry = true;
	std::cout << "Welchen Song willst du spielen?\n" << std::endl;
	std::cin >> song;
	std::string songPath = "Music\\" + playlist[song];
	try
	{
		for (size_t i = 0; i < playlist.size(); i++)
		{
			if (i == song) {
				std::cout << "Es spieltD: ";
				std::cout << playlist[i] << std::endl;
				PlaySoundA(songPath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//endless Loop.
				makeEntry = false;
				ii=song+1;
			}
		}
		
		if (ii == song + 1)
		{
			for (size_t i = ii; i < playlist.size(); i++)
			{
				std::string songEnding{ playlist[ii] };
				songPath = "Music\\" + songEnding;
				std::cout << "Es spielt: ";
				std::cout << playlist[i] << std::endl;
				PlaySoundA(songPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		if (makeEntry)
		{
			std::cout << "Song nicht gefunden!" << std::endl;
		}
		
	}
	catch (const std::exception&)
	{
		std::cout << "ERROR!\n" << std::endl;
	}
	clear();
}
void playList(const std::vector<std::string>& playlist) {
	int song{};
	int ii{};
	bool makeEntry = true;
	std::cout << "Welchen Song willst du spielen?\n" << std::endl;
	std::cin >> song;
	std::string songPath = "Music\\" + playlist[song];
	try
	{
		for (size_t i = 0; i < playlist.size(); i++)
		{
			if (i == song) {
				std::cout << "Es spielt: ";
				std::cout << playlist[i] << std::endl;
				PlaySoundA(songPath.c_str(), NULL, SND_FILENAME);
				makeEntry = false;
				if (makeEntry)
				{
					std::cerr << "Song nicht gefunden!" << std::endl;
					break;
				}
				ii = song + 1;
				if (ii == song + 1)
				{
					for (size_t i = ii; i < playlist.size(); i++)
					{
						std::string songEnding{ playlist[i] };
						songPath = "Music\\" + songEnding;
						std::cout << "Es spielt: ";
						std::cout << playlist[i] << std::endl;
						PlaySoundA(songPath.c_str(), NULL, SND_FILENAME);
					}
				}
			}
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "ERROR!\n" << std::endl;
	}
	clear();
	
}
/*void addSong(std::vector<std::string>& playlist, std::ofstream& fileForSave) {//eventuell zu gebrauchen für die playlists. um zu prüfen ob der song schon in der playlist ist. der file wird gerade nicht gefüllt, wenn er es soll dann in giveVecEntry() hinzufügen. Eventuell doch nicht unbedingt brauchbar, mann kann auch einfach duch den Vec gehen wo die gelesenden werte drin sind und dann hinzufügen in den anderen Vec/playlist.
	bool makeEntry = true;
	std::string songName{};
	try
	{
		std::cout<< "Gib Songnamen + endung der Datei an." << std::endl;
		std::getline(std::cin, songName);
		if (std::cin.fail())
		{
			killInput();
			std::cerr << "Problem beim einlesen der Eingabe" << std::endl;
			return;//Vielleicht währe ein continue sinnvoller.
		}
		sort(playlist.begin(), playlist.end());
		for (const auto& s : playlist)
		{
			if (s == songName)
			{
				std::cout << "Eintrag schon vorhanden!" << std::endl;
				makeEntry = false;
				break;
			}
		}
		if (makeEntry)
		{
			std::cout << "Eintrag hinzugefügt!" << std::endl;
			playlist.push_back(songName);
			fileForSave << songName << std::endl;
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "Generelles Problem beim Hinzufügen des Songs!"<<std::endl;
	}
	clear();
}

*/
