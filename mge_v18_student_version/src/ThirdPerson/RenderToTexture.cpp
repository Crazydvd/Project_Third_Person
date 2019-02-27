#include "ThirdPerson/RenderToTexture.hpp"
#include <iostream>

RenderToTexture::RenderToTexture()
{
	createFramebuffer();
	createTexture();
	configureFramebuffer();
	checkFramebuffer();
	unbindFramebuffer();
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