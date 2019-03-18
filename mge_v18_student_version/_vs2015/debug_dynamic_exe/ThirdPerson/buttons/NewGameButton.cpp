#include <cassert>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/NewGameButton.hpp"
#include "ThirdPerson/config.hpp"

NewGameButton::NewGameButton(sf::RenderWindow * aWindow, Room* pRoom, UserInterface* pUI, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom), _userInterface(pUI)
{

}

void NewGameButton::OnClick()
{
	MenuButton::OnClick();
	std::ofstream savefile;
	savefile.open("save.txt", std::fstream::in | std::fstream::trunc);
	savefile << "1";
	savefile.close();


	_room->Initialize();
	_room->LoadLevel(1);
	_userInterface->QueueClear();
}

NewGameButton::~NewGameButton()
{
	//dtor
}
