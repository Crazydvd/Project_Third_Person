#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "ThirdPerson/UITexture.hpp"
#include "mge/core/GameObject.hpp"
#include <iostream>

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
	void draw();
	virtual void update(float pStep);

private:
	sf::RenderWindow * _window;
	std::vector<UITexture*> _objects;

	UserInterface(const UserInterface&);
	UserInterface& operator=(const UserInterface&);
};

#endif // USERINTERFACE_HPP
