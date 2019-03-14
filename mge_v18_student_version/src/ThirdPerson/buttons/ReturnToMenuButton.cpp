#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/buttons/ReturnToMenuButton.hpp"
#include "ThirdPerson/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

ReturnToMenuButton::ReturnToMenuButton(sf::RenderWindow * aWindow, Room* pRoom, TPerson* pGame, std::string fileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName) : MenuButton(aWindow, fileName, hoverFileName, pPosition, pName), _room(pRoom), _game(pGame)
{

}

void ReturnToMenuButton::OnClick()
{
	_room->PlayAnimation("menu", false);
	MenuButton::OnClick();

	_room->DisablePause();
	_room->Deinitialize();
}

ReturnToMenuButton::~ReturnToMenuButton()
{
	//dtor
}
