#ifndef UITEXTURE_HPP
#define UITEXTURE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"

/**
 * Very simple class capable of rendering a simple piece of text through SFML.
 */
class UITexture
{
public:
	UITexture(sf::RenderWindow* aWindow, std::string pfileName, std::string pName = "UITexture");
	virtual ~UITexture();
	sf::IntRect GetRect();
	sf::Vector2f UITexture::GetPosition();
	std::string GetName();

	virtual void OnClick();
	virtual void draw();

private:
	UITexture(const UITexture&);
	UITexture& operator=(const UITexture&);
protected:
	sf::RenderWindow * _window;
	std::string _name;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

#endif // DEBUGHUD_HPP
