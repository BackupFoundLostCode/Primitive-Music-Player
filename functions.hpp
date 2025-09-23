#pragma once
#include <iostream>
#include <filesystem>
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
void giveVecEntry(std::vector<std::string>& playlist) {//vector zu anfag des programms mit den eintr�gen aus der save.tyt f�llen sonst kann man ja nichts abspielen nachhher.
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
			return;//Vielleicht w�hre ein continue sinnvoller.
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
			std::cout << "Eintrag hinzugef�gt!" << std::endl;
			playlist.push_back(songName);
			fileForSave << songName << std::endl;
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "Generelles Problem beim Hinzuf�gen des Songs!"<<std::endl;
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
	//irgend wie Palylists erstellen k�nnen.
	//logik stimmt so eignetlich aber playsound funktiooniert lieder nicht damit.
	killInput();
	int song{};
	int ii{};
	bool makeEntry = true;
	std::cout << "Welchen Song willst du spielen?\n" << std::endl;
	std::cin >> song;
	std::string songEnding{ playlist[song] };//wenn ich etwas eingebe was �ber dem index liegt schmiert das programm ab, doch beheben. Auch wird wenn an beim songausw�hlen etwas anders als zahlen eingibt einfach der 0 index gestatet.
	std::string songPath = "Music\\" + songEnding;
	try
	{
		for (size_t i = 0; i < playlist.size(); i++)
		{
			if (i == song) {
				std::cout << "Es spieltD: ";
				std::cout << playlist[i] << std::endl;
				PlaySoundA(songPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
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