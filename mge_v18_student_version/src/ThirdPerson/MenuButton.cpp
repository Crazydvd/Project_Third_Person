#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/MenuButton.hpp"
#include "ThirdPerson/config.hpp"

MenuButton::MenuButton(sf::RenderWindow * aWindow, std::string fileName, std::string pName) : UITexture(aWindow, fileName, pName)
{
	assert(_window != NULL);

	if (!_texture.loadFromFile(config::THIRDPERSON_TEXTURE_PATH + fileName)) {
		std::cout << "Could not load texture, exiting..." << std::endl;
		return;
	}

	_sprite.setTexture(_texture);
	std::cout << _sprite.getTextureRect().height;

}

void MenuButton::OnClick() {
	std::cout << _name << "clock";
}

MenuButton::~MenuButton()
{
	//dtor
}
