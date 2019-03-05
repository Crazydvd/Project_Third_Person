#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include "ThirdPerson/UITexture.hpp"
#include "ThirdPerson/config.hpp"

UITexture::UITexture(sf::RenderWindow * aWindow, std::string fileName, std::string pName) : _window(aWindow), _name(pName), _texture(), _sprite()
{
	assert(_window != NULL);

	if (!_texture.loadFromFile(config::THIRDPERSON_TEXTURE_PATH + fileName)) {
		std::cout << "Could not load texture, exiting..." << std::endl;
		return;
	}

	_sprite.setTexture(_texture);
	std::cout << _sprite.getTextureRect().height;

}

void UITexture::OnClick() {
	std::cout << _name << "click";
}

sf::IntRect UITexture::GetRect() {
	return _sprite.getTextureRect();
}

sf::Vector2f UITexture::GetPosition() {
	return _sprite.getPosition();
}

std::string UITexture::GetName() {
	return _name;
}

UITexture::~UITexture()
{
	//dtor
}

void UITexture::draw()
{
	glDisable( GL_CULL_FACE );
	glActiveTexture(GL_TEXTURE0);
	_window->pushGLStates();
	_window->draw(_sprite);
	_window->popGLStates();
}
