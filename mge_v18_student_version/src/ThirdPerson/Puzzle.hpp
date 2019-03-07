#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <string>
#include <glm/glm.hpp>
#include "SFML/Graphics/RenderWindow.hpp"
#include <mge/core/GameObject.hpp>
#include "ThirdPerson/Timer.hpp"

//class GameObject;
class RenderWindow;
class World;

class Puzzle : public GameObject
{
	public:
		Puzzle(sf::RenderWindow* pWindow, World* pWorld, int plevelIndex, std::string pName = "puzzle", glm::vec3 pPosition = glm::vec3(0,0,0));

		virtual ~Puzzle();
		virtual void update(float pStep);
		void LoadObject(std::string pModel, std::string pTexture);
		std::vector<GameObject*> getObjects();

		Timer* PuzzleTimer;
	private:
		bool _completed;
		int _levelIndex;
		int _victoryDelay;
		World* _world;
		std::vector<GameObject*> _puzzleObjects;
		sf::RenderWindow* _window;
		void checkOnePuzzle();
};

#endif // !PUZZLE_HPP

