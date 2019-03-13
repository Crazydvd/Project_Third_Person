#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/BackToMainButton.hpp"
#include "ThirdPerson/config.hpp"

BackToMainButton::BackToMainButton(sf::RenderWindow * aWindow, Room* pRoom, TPerson* pGame, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom), _game(pGame)
{

}

void BackToMainButton::OnClick() {
	_game->MainMenu->LoadMainMenu(_room, _game);
}

BackToMainButton::~BackToMainButton()
{
	//dtor
}
