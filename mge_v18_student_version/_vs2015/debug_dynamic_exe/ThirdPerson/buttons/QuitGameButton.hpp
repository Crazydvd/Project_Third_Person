#ifndef QUITGAMEBUTTON_HPP
#define QUITGAMEBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"

class QuitGameButton : public MenuButton
{
public:
	QuitGameButton(sf::RenderWindow* aWindow, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "QuitMenuButton");
	void OnClick();
	virtual ~QuitGameButton();

private:
	sf::Texture _hoverTexture;
	QuitGameButton(const QuitGameButton&);
	QuitGameButton& operator=(const QuitGameButton&);
protected:
};

#endif // NEWGAMEBUTTON_HPP
