#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/UITexture.hpp"
#include "ThirdPerson/buttons/MenuButton.hpp"

#include <iostream>

class Room;

/**
 * Very simple class capable of rendering a simple piece of text through SFML.
 */
class UserInterface : public GameObject
{
public:
	UserInterface(sf::RenderWindow * aWindow, std::string pName = "UserInterface",
		glm::vec3 pPosition = glm::vec3(0.0f, 0.0f, 0.0f));
	virtual ~UserInterface();
	void Add(UITexture* pObject);
	void AddButton(MenuButton* pObject);
	void LoadMainMenu(Room* pRoom);
	void QueueClear();
	void EmptyInterface();
	void draw();
	virtual void update(float pStep);

	bool Paused = false;

private:
	sf::RenderWindow * _window;
	std::vector<UITexture*> _objects;
	std::vector<MenuButton*> _buttons;

	bool _queueClearing = false;

	UserInterface(const UserInterface&);
	UserInterface& operator=(const UserInterface&);
};

#endif // USERINTERFACE_HPP
