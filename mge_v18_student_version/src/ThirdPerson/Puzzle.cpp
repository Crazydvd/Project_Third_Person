#include "ThirdPerson/Puzzle.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"
#include "mge/behaviours/MouseRotatingBehaviour.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"

Puzzle::Puzzle(sf::RenderWindow* pWindow, World* pWorld) : _window(pWindow), _world(pWorld)
{

}

GameObject* Puzzle::LoadObject(std::string pModel, std::string pTexture)
{
	GameObject* object = new GameObject("puzzleObject1", glm::vec3(0, 0, 0));
	object->setMesh(Mesh::load(config::THIRDPERSON_MODEL_PATH + pModel));
	object->setMaterial(new LitTextureMaterial(Texture::load(config::THIRDPERSON_TEXTURE_PATH + pTexture)));
	object->setBehaviour(new MouseRotatingBehaviour(_window, _world));
	_world->add(object);
	TPerson::puzzleObjects.push_back(object);

	return object;
}