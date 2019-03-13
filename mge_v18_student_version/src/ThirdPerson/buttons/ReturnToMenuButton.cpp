#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/ReturnToMenuButton.hpp"
#include "ThirdPerson/config.hpp"

ReturnToMenuButton::ReturnToMenuButton(sf::RenderWindow * aWindow, Room* pRoom, TPerson* pGame, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom), _game(pGame)
{

}

void ReturnToMenuButton::OnClick()
{
	MenuButton::OnClick();
	_room->TogglePause();
}

void ReturnToMenuButton::OnClick()
{
	_room->DisablePause();
	_room->Deinitialize();
	_game->MainMenu->LoadMainMenu(_room, _game);
}

ReturnToMenuButton::~ReturnToMenuButton()
{
	//dtor
}
