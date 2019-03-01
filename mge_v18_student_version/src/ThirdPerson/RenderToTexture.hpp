#ifndef RENDERTOTEXTURE_HPP
#define RENDERTOTEXTURE_HPP
#include "GL/glew.h"
#include "mge/core/Texture.hpp"

class RenderToTexture
{
public:
	RenderToTexture();

	void bindFramebuffer();
	void unbindFramebuffer();
	Texture* getTexture() { return _renderedTexture; };

private:
	void createFramebuffer();
	void createTexture();
	void createDepthbuffer();
	void configureFramebuffer();
	bool checkFramebuffer();

	Texture* _renderedTexture; //The texture that we're going to render to.
	GLuint _framebufferName; // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint _depthRenderbuffer; //the depth buffer.
};

#endif // !RENDERTOTEXTURE_HPP
