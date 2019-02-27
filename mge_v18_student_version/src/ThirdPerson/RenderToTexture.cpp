#include "ThirdPerson/RenderToTexture.hpp"
#include <iostream>

RenderToTexture::RenderToTexture()
{
	createTexture();
	createFramebuffer();
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

void RenderToTexture::createDepthbuffer()
{
	// The depth buffer
	/*glGenRenderbuffers(1, &_depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderbuffer);*/
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
	glViewport(0, 0, 800, 600); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}

void RenderToTexture::unbindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 800, 600); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}

bool RenderToTexture::checkFramebuffer()
{
	return !(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE);
}