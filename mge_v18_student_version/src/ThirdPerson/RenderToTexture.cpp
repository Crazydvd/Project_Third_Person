#include "ThirdPerson/RenderToTexture.hpp"
#include <iostream>

RenderToTexture::RenderToTexture()
{
	createFramebuffer();

	createTexture();

	createDepthbuffer();

	configureFramebuffer();

	checkFramebuffer();

	bindFramebuffer();
}

void RenderToTexture::createFramebuffer()
{
	GLuint _framebufferName = 0;
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
	glGenRenderbuffers(1, &_depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderbuffer);

	// Set "_renderedTexture" as our colour attachment #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _renderedTexture->getId(), 0);
}

void RenderToTexture::configureFramebuffer()
{
	// Set the list of draw buffers
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers;
}

void RenderToTexture::bindFramebuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _framebufferName);
	glViewport(0, 0, 1024, 768); // Render on the whole framebuffer, complete from the lower left corner to the upper right
}

bool RenderToTexture::checkFramebuffer()
{
	// check if the framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		return false;
	}
}