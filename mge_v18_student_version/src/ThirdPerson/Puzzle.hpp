#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <string>
#include "SFML/Graphics/RenderWindow.hpp"

class GameObject;
class RenderWindow;
class World;

class Puzzle
{
public:
	Puzzle(sf::RenderWindow* pWindow, World* pWorld);
	~Puzzle();

	GameObject* LoadObject(std::string pModel, std::string pTexture);

private:
	sf::RenderWindow* _window;
	World* _world;

};

#endif // !PUZZLE_HPP

