#include <iostream>
#include "ThirdPerson/RenderToTexture.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Camera.hpp"
#include "ThirdPerson/TPerson.hpp"
#include "mge/materials/ColorMaterial.hpp"

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
	std::vector<AbstractMaterial*> materials;

	for (int i = 0; i < pObjects.size(); i++)
	{
		materials.push_back(pObjects[i]->getMaterial());
	}

	Camera* camera = _tPerson->GetMainCamera();
	glm::mat4 camTransform = camera->getWorldTransform();
	bindFramebuffer();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->setTransform(pTransform);
	float cameraFOV = camera->GetFOV();
	camera->SetFOV(30.0f);

	for (int i = 0; i < pObjects.size(); i++)
	{
		pObjects[i]->setMaterial(pRenderMaterial);
	}

	_tPerson->Render();
	unbindFramebuffer();

	for (int i = 0; i < pObjects.size(); i++)
	{
		pObjects[i]->setMaterial(materials[i]);
	}
	
	camera->setTransform(camTransform);
	camera->SetFOV(cameraFOV);
}

void RenderToTexture::Render(std::vector<GameObject*> pObjects, glm::mat4 pTransform)
{
	AbstractMaterial* white = new ColorMaterial(glm::vec3(1, 1, 1));

	Camera* camera = _tPerson->GetMainCamera();
	glm::mat4 camTransform = camera->getWorldTransform();
	bindFramebuffer();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->setTransform(pTransform);
	float cameraFOV = camera->GetFOV();
	camera->SetFOV(30.0f);

	_tPerson->Render();
	unbindFramebuffer();

	camera->setTransform(camTransform);
	camera->SetFOV(cameraFOV);
}

void RenderToTexture::Render(std::vector<GameObject*> pObjects, AbstractMaterial* pRenderMaterial, std::vector<GameObject*> pExcludedObjects, glm::mat4 pTransform)
{
	AbstractMaterial* white = new ColorMaterial(glm::vec4(1, 1, 1, 1));

	std::vector<AbstractMaterial*> materials;

	for (int i = 0; i < pObjects.size(); i++)
	{
		materials.push_back(pObjects[i]->getMaterial());
	}

	std::vector<AbstractMaterial*> excludedMaterials;

	for (int i = 0; i < pExcludedObjects.size(); i++)
	{
		excludedMaterials.push_back(pExcludedObjects[i]->getMaterial());
	}

	Camera* camera = _tPerson->GetMainCamera();
	glm::mat4 camTransform = camera->getWorldTransform();
	bindFramebuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);

	camera->setTransform(pTransform);
	float cameraFOV = camera->GetFOV();
	//camera->SetFOV(30.0f);

	for (int i = 0; i < pObjects.size(); i++)
	{
		pObjects[i]->setMaterial(pRenderMaterial);
	}

	for (int i = 0; i < pExcludedObjects.size(); i++)
	{
		pExcludedObjects[i]->setMaterial(white);
	}
	//glm::vec3 translate = glm::vec3(0, -3, 1);

	//pExcludedObjects[0]->translate(translate);

	_tPerson->Render();
	unbindFramebuffer();

	//pExcludedObjects[0]->translate(-translate);

	for (int i = 0; i < pObjects.size(); i++)
	{
		pObjects[i]->setMaterial(materials[i]);
	}

	for (int i = 0; i < pExcludedObjects.size(); i++)
	{
		pExcludedObjects[i]->setMaterial(excludedMaterials[i]);
	}

	camera->setTransform(camTransform);
	camera->SetFOV(cameraFOV);
}

void RenderToTexture::Render(std::vector<GameObject*> pObjects, std::vector<GameObject*> pExcludedObjects, glm::mat4 pTransform)
{
	AbstractMaterial* white = new ColorMaterial(glm::vec3(1, 1, 1));

	std::vector<AbstractMaterial*> excludedMaterials;

	for (int i = 0; i < pExcludedObjects.size(); i++)
	{
		excludedMaterials.push_back(pExcludedObjects[i]->getMaterial());
	}

	Camera* camera = _tPerson->GetMainCamera();
	glm::mat4 camTransform = camera->getWorldTransform();
	bindFramebuffer();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->setTransform(pTransform);
	float cameraFOV = camera->GetFOV();
	camera->SetFOV(30.0f);

	for (int i = 0; i < pExcludedObjects.size(); i++)
	{
		pExcludedObjects[i]->setMaterial(white);
	}

	_tPerson->Render();
	unbindFramebuffer();

	for (int i = 0; i < pExcludedObjects.size(); i++)
	{
		pExcludedObjects[i]->setMaterial(excludedMaterials[i]);
	}

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