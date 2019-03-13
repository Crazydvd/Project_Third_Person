#include <cassert>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/ContinueButton.hpp"
#include "ThirdPerson/config.hpp"

ContinueButton::ContinueButton(sf::RenderWindow * aWindow, Room* pRoom, UserInterface* pUI, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom), _userInterface(pUI)
{

}

void ContinueButton::OnClick() {
	MenuButton::OnClick();
	
	int level;

	std::string line;
	std::ifstream myfile("save.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line;
			level = std::stoi(line);
		}
		myfile.close();
	}
	else {
		std::ofstream savefile;
		savefile.open("save.txt");
		savefile << "1";
		savefile.close();	
		level = 1;
	}

	_room->Initialize();
	_room->LoadLevel(level);
	_userInterface->QueueClear();
}

ContinueButton::~ContinueButton()
{
	//dtor
}
