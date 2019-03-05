#ifndef RENDERTOTEXTURE_HPP
#define RENDERTOTEXTURE_HPP
#include "GL/glew.h"
#include <vector>
#include "glm.hpp"

class Texture;
class GameObject;
class AbstractMaterial;
class TPerson;
class mat4;

class RenderToTexture
{
public:
	RenderToTexture();

	void bindFramebuffer();
	void unbindFramebuffer();
	Texture* getTexture() { return _renderedTexture; };

	void setTPerson(TPerson* pTPerson);

	void Render(std::vector<GameObject*> pObjects, AbstractMaterial* pRenderMaterial, glm::mat4 pTransform);
	void Render(std::vector<GameObject*> pObjects, glm::mat4 pTransform);
	void Render(std::vector<GameObject*> pObjects, AbstractMaterial* pRenderMaterial, std::vector<GameObject*> pExcludedObjects, glm::mat4 pTransform);
	void Render(std::vector<GameObject*> pObjects, std::vector<GameObject*> pExcludedObjects, glm::mat4 pTransform);

private:
	void createFramebuffer();
	void createTexture();
	void configureFramebuffer();
	bool checkFramebuffer();

	Texture* _renderedTexture; //The texture that we're going to render to.
	GLuint _framebufferName; // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint _depthRenderbuffer; //the depth buffer.

	TPerson* _tPerson = NULL;
};

#endif // !RENDERTOTEXTURE_HPP
