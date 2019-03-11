#ifndef MENUBUTTON_HPP
#define MENUBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/UITexture.hpp"
#include "ThirdPerson/Audio.hpp"

/**
 * Very simple class capable of rendering a simple piece of text through SFML.
 */
class MenuButton : public UITexture
{
public:
	MenuButton(sf::RenderWindow* aWindow, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "MenuButton");
	virtual ~MenuButton();
	//void draw();
	virtual void OnClick();
	void OnHover();
	void OnStopHover();

private:
	sf::Texture _hoverTexture;
	MenuButton(const MenuButton&);
	MenuButton& operator=(const MenuButton&);

	Audio _audio;
	bool _played = false;
};

#endif // MENUBUTTON_HPP
