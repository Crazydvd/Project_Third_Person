#ifndef MenuButton_HPP
#define MenuButton_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/UITexture.hpp"

/**
 * Very simple class capable of rendering a simple piece of text through SFML.
 */
class MenuButton : public UITexture
{
public:
	MenuButton(sf::RenderWindow* aWindow, std::string pfileName, std::string pName = "MenuButton");
	virtual ~MenuButton();
	//void draw();
	void OnClick();

private:
	MenuButton(const MenuButton&);
	MenuButton& operator=(const MenuButton&);
protected:
};

#endif // DEBUGHUD_HPP
