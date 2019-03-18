#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/LevelSelectButton.hpp"
#include "ThirdPerson/config.hpp"

LevelSelectButton::LevelSelectButton(sf::RenderWindow * aWindow, Room* pRoom, TPerson* pGame, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom), _game(pGame)
{

}

void LevelSelectButton::OnClick()
{
	MenuButton::OnClick();
	std::cout << "level select";

	_game->MainMenu->LoadLevelSelect(_room, _game);
}

LevelSelectButton::~LevelSelectButton()
{
	//dtor
}
