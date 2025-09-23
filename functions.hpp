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
void giveVecEntry(std::vector<std::string>& playlist) {//vector zu anfag des programms mit den einträgen aus der save.tyt füllen sonst kann man ja nichts abspielen nachhher.
	std::string ram{};
	std::ifstream read{ "save.txt" };//muss auf save.txt zugreifen, hoffe das geht ertsmal so.
	while (getline(read, ram)) {
		playlist.push_back(ram);
	}
}
void addSong(std::vector<std::string>& playlist,std::ofstream& fileForSave) {
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
void showPlaylist(const std::vector<std::string>& playlist) {
	std::cout << "Playlist: " << "\n"<<std::endl;
	for (size_t i = 0; i < playlist.size(); i++)
	{
		std::cout <<"["<<i<<"]"<< playlist[i] << std::endl;
	}
	std::cout << "\n";
}
void keepPlaying(int& song, const std::vector<std::string>& playlist) {
	for (size_t i = song+1; i < playlist.size(); i++)
	{
		std::cout << "Es spielt: ";
		std::cout << playlist[i] << std::endl;
		//PlaySoundA(songPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
	}
	
}
void playMusic(const std::vector<std::string>& playlist) {
	//irgend wie Palylists erstellen können.
	//logik stimmt so eignetlich aber playsound funktiooniert lieder nicht damit.
	//ist ja wie playList() soll aber halt im hintergrund laufen.
	killInput();
	int song{};
	int ii{};
	bool makeEntry = true;
	std::cout << "Welchen Song willst du spielen?\n" << std::endl;
	std::cin >> song;
	std::string songPath = "Music\\" + playlist[song];
	std::string alias{ "mySong" };
	try
	{
		for (size_t i = 0; i < playlist.size(); i++)
		{
			if (i == song) {
				std::cout << "Es spieltD: ";
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
	killInput();
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
		/*if (ii == song + 1)
		{
			for (size_t i = ii; i < playlist.size(); i++)
			{
				std::cout << "I ist: " << i;
				std::string songEnding{ playlist[i] };
				songPath = "Music\\" + songEnding;
				std::cout << "Es spielt: ";
				std::cout << playlist[i] << std::endl;
				PlaySoundA(songPath.c_str(), NULL, SND_FILENAME);
			}
		}
		if (makeEntry)
		{
			std::cerr << "Song nicht gefunden!" << std::endl;
		}
		*/
	}
	catch (const std::exception&)
	{
		std::cerr << "ERROR!\n" << std::endl;
	}
	clear();
	
}

