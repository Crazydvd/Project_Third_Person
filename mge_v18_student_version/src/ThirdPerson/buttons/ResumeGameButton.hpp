#ifndef RESUMEGAMEBUTTON_HPP
#define RESUMEGAMEBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/Room.hpp"

class ResumeGameButton : public MenuButton
{
public:
	ResumeGameButton(sf::RenderWindow* aWindow, Room* pRoom, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "QuitMenuButton");
	void OnClick();
	virtual ~ResumeGameButton();

private:
	sf::Texture _hoverTexture;
	ResumeGameButton(const ResumeGameButton&);
	ResumeGameButton& operator=(const ResumeGameButton&);
	Room* _room;
protected:
};

#endif // NEWGAMEBUTTON_HPP
