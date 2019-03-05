#include "mge/behaviours/ClickBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "ThirdPerson/Ray.hpp"
#include "ThirdPerson/config.hpp"

ClickBehaviour::ClickBehaviour(sf::RenderWindow* pWindow, World* pWorld): AbstractBehaviour(), _window(pWindow), _world(pWorld)
{
}

void ClickBehaviour::update(float pStep)
{
	
	//Rotating with mouse
	if (!_mousePressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		_mousePressed = true;
		sf::Vector2i vec2 = sf::Mouse::getPosition(*_window);
		Ray mouseray = Ray::MouseRay(_window, 60.0f, _world);
		std::cout << vec2.x << " - " << vec2.y << std::endl;

		sf::Texture example;
		sf::Sprite sprite;

		example.loadFromFile(config::THIRDPERSON_TEXTURE_PATH + "runicfloor.png");
		sprite.setTexture(example);
		_window->draw(sprite);
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		_mousePressed = false;
	}
};