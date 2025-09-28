#pragma once
#include <iostream>
#include <filesystem>
#include <fstream> 
#include <Windows.h>
inline void killInput() {
	std::cin.clear();
	std::cin.ignore(50, '\n');
}
inline void clear() {
	system("pause");
	system("cls");
}
void existsDirectory(const std::filesystem::path& pathForMusic) {
	if (std::filesystem::create_directory(pathForMusic))
	{
		std::cout << "Folder created!\n" << std::endl;
	}
	else
	{
		std::cerr << "Folder could not be created or already exists.\n" << std::endl;
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
inline void showPlaylist(const std::vector<std::string>& playlist) {
	std::cout << "Title: " << "\n"<<std::endl;
	for (size_t i = 0; i < playlist.size(); i++)
	{
		std::cout <<"["<<i<<"]"<< playlist[i] << std::endl;
	}
	std::cout << "\n";
}
void playMusic(const std::vector<std::string>& playlist) {
	//ist ja wie playList() soll aber halt im hintergrund laufen. Soll das eigentliche programm werden, also das es wie PlaySoundA() ist nur das es eben nicht dann duchskipt sondern alles nacheidner abspielt aber eben mann während dessen noch das programm nutzen kann. Wie PlayList() nur das mann eben möglichkeiten von PlaySoundA() hat ohne das es dann die lsite bis zum ende skippt.
	int song{};
	int ii{};
	bool makeEntry = true;
	std::cout << "Which song do you want to play?\n" << std::endl;
	std::cin >> song;
	std::string songPath = "Music\\" + playlist[song];
	try
	{
		for (size_t i = 0; i < playlist.size(); i++)
		{
			if (i == song) {
				std::cout << "It plays: ";
				std::cout << playlist[i] << std::endl;
				PlaySoundA(songPath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//endloser loop.
				makeEntry = false;
				ii=song+1;
			}
		}
		
		if (ii == song + 1)//wenn ich es hier schaffe dann macht er das autoplay.
		{
			for (size_t i = ii; i < playlist.size(); i++)
			{
				std::string songEnding{ playlist[ii] };
				songPath = "Music\\" + songEnding;
				std::cout << "It plays: ";
				std::cout << playlist[i] << std::endl;
				PlaySoundA(songPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
		if (makeEntry)
		{
			std::cout << "Song not found!" << std::endl;
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
	char answer{};
	bool songContinue{false};
	std::cout << "Autoplay? Y or N.\n" << std::endl;
	std::cin >> answer;
	if (answer=='Y' || answer=='y')
	{
		songContinue = true;
	}
	std::cout << "Which song do you want to play?\n" << std::endl;
	std::cin >> song;
	std::string songPath = "Music\\" + playlist[song];
	try
	{
		for (size_t i = 0; i < playlist.size(); i++)
		{
			if (i==song)
			{
				if (songContinue==false)
				{
					for (size_t i = song; i < playlist.size(); i++)
					{
						//Change playsound to a better alternative.
						std::string songEnding{ playlist[i] };
						songPath = "Music\\" + songEnding;
						std::cout << "It plays: ";
						std::cout << playlist[i] << std::endl;
						PlaySoundA(songPath.c_str(), NULL, SND_FILENAME);
					}
				}
				else if (songContinue==true)
				{
					while (true)
					{
						for (size_t i = song; i < playlist.size(); i++)
						{
							std::string songEnding{ playlist[i] };
							songPath = "Music\\" + songEnding;
							std::cout << "It plays: ";
							std::cout << playlist[i] << std::endl;
							PlaySoundA(songPath.c_str(), NULL, SND_FILENAME);
						}
						song = 0;
						continue;
					}
				}
			}
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "ERROR!\n" << std::endl;
	}
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