#include <iostream>
#include "ThirdPerson/RenderToTexture.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core//Camera.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/core/Renderer.hpp"

RenderToTexture::RenderToTexture()
{
	createFramebuffer();
	createTexture();
	configureFramebuffer();
	checkFramebuffer();
	unbindFramebuffer();
}

void RenderToTexture::setTPerson(TPerson* pTPerson)
{
	_tPerson = pTPerson;
}

void RenderToTexture::Render(std::vector<GameObject*> pObjects, AbstractMaterial* pRenderMaterial, glm::mat4 pTransform)
{
	Camera* camera = _tPerson->GetMainCamera();
	glm::mat4 camTransform = camera->getWorldTransform();
	bindFramebuffer();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->setTransform(pTransform);
	float cameraFOV = camera->GetFOV();
	camera->SetFOV(30.0f);
	Renderer* renderer = _tPerson->getRenderer();
	World* world = _tPerson->GetWorld();

	for (size_t i = 0; i < pObjects.size(); i++)
	{
		renderer->render(world, pObjects[i], pRenderMaterial, camera, true);
	}
	unbindFramebuffer();

	camera->setTransform(camTransform);
	camera->SetFOV(cameraFOV);
}

void RenderToTexture::createFramebuffer()
{
	_framebufferName = 0;
	glGenFramebuffers(1, &_framebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, _framebufferName);
}

void RenderToTexture::createTexture()
{
	_renderedTexture = Texture::GetEmptyTexture();
}

void RenderToTexture::configureFramebuffer()
{
	// Set "_renderedTexture" as our colour attachment #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, _renderedTexture->getId(), 0);

	// Set the list of draw buffers
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers;
}

void RenderToTexture::bindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _framebufferName);
}

void RenderToTexture::unbindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool RenderToTexture::checkFramebuffer()
{
	return !(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE);
}