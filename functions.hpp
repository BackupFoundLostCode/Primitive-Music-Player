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

