#include <cassert>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/LoadLevelButton.hpp"
#include "ThirdPerson/config.hpp"

LoadLevelButton::LoadLevelButton(sf::RenderWindow * aWindow, Room* pRoom, UserInterface* pUI, int pLevel, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom), _userInterface(pUI), _level(pLevel)
{

}

void LoadLevelButton::OnClick() {
	_room->Initialize();
	_room->LoadLevel(_level);
	_userInterface->QueueClear();
}

LoadLevelButton::~LoadLevelButton()
{
	//dtor
}
