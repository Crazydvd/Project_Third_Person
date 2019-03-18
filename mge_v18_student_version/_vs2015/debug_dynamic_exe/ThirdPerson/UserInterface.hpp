#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/UITexture.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"

#include <iostream>

class Room;
class TPerson;

/**
 * Very simple class capable of rendering a simple piece of text through SFML.
 */
class UserInterface : public GameObject
{
public:
	UserInterface(sf::RenderWindow * aWindow, std::string pName = "UserInterface",
		glm::vec3 pPosition = glm::vec3(0.0f, 0.0f, 0.0f));
	virtual ~UserInterface();
	void Add(UITexture* pObject, bool topLayer = false);
	void AddButton(MenuButton* pObject);
	void LoadMainMenu(Room* pRoom, TPerson* pGame);
	void LoadLevelSelect(Room* pRoom, TPerson* pGame);
	void QueueClear();
	void EmptyInterface();
	void draw();
	virtual void update(float pStep);

	bool Paused = false;

private:
	sf::RenderWindow * _window;
	std::vector<UITexture*> _objects;
	std::vector<UITexture*> _topLayer;
	std::vector<MenuButton*> _buttons;
	UITexture* _level1;
	UITexture* _level2;
	UITexture* _level3;
	UITexture* _level4;
	UITexture* _level5;
	UITexture* _string;

	bool _queueClearing = false;

	UserInterface(const UserInterface&);
	UserInterface& operator=(const UserInterface&);
};

#endif // USERINTERFACE_HPP
