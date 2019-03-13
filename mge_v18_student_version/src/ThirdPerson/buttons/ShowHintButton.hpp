#ifndef SHOWHINTBUTTON_HPP
#define SHOWHINTBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "glm.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"
#include "ThirdPerson/Room.hpp"
#include "ThirdPerson/UITexture.hpp"

class ShowHintButton : public MenuButton
{
public:
	ShowHintButton(sf::RenderWindow* aWindow, UITexture* pTexture, bool* pShowingHint, float* pTimer, std::string pfileName, std::string hoverFileName, glm::vec2 pPosition, std::string pName = "QuitMenuButton");
	void OnClick();
	virtual ~ShowHintButton();

private:
	sf::Texture _hoverTexture;
	ShowHintButton(const ShowHintButton&);
	ShowHintButton& operator=(const ShowHintButton&);
	UITexture* _texture;
	bool* _showingHint;
	float* _timer;
protected:
};

#endif // NEWGAMEBUTTON_HPP
