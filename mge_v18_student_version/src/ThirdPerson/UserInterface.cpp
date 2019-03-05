#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Music.hpp>
#include "ThirdPerson/UserInterface.hpp"
#include "ThirdPerson/MenuButton.hpp"
#include "ThirdPerson/config.hpp"

UserInterface::UserInterface(sf::RenderWindow * aWindow, std::string pName, glm::vec3 pPosition)
	: GameObject(pName, pPosition), _window(aWindow)
{
	assert(_window != NULL);
	UserInterface::_objects = std::vector<UITexture*>();

	UITexture* texture = new UITexture(_window, "corkboard.png");

	MenuButton* startGame = new MenuButton(_window, "newgamepin.png");
	this->Add(startGame);
	//this->Add(texture);
}

void UserInterface::update(float pStep) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
	//check for hovering over objects
	for (int i = _objects.size() - 1; i > -1; i--) {
		sf::Vector2f objPos = _objects[i]->GetPosition();
		sf::IntRect objRect = _objects[i]->GetRect();

		if ((mousePos.x > objPos.x) && (mousePos.x < objPos.x + objRect.width) &&
			(mousePos.y > objPos.y) && (mousePos.y < objPos.y + objRect.height))
		{
			_objects[i]->OnClick();
		}
	}
}

UserInterface::~UserInterface()
{
	//dtor
}

void UserInterface::Add(UITexture* pObject) {
	_objects.push_back(pObject);
}

void UserInterface::draw()
{
	for (int i = _objects.size() - 1; i > -1; i--) {
		_objects[i]->draw();
	}
}
