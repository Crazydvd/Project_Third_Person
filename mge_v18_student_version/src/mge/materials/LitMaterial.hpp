#ifndef LITMATERIAL_HPP
#define LITMATERIAL_HPP

#include "GL/glew.h"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/core/Light.hpp"
#include <vector>

class ShaderProgram;

/**
 * This is about the simplest material we can come up with, it demonstrates how to
 * render a single color material without caching, passing in all the matrices we require separately.
 */
class LitMaterial : public AbstractMaterial
{
    public:
		LitMaterial(glm::vec3 pAmbient = glm::vec3(1, 1, 1), glm::vec3 pSpecular = glm::vec3(1, 1, 1));
        virtual ~LitMaterial();

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        //in rgb values
        void setDiffuseColor (glm::vec3 pDiffuseColor);
		void setAmbientColor (glm::vec3 pAmbientColor);
		void setSpecularColor(glm::vec3 pSpecularColor);
		void setShininess(int pShininess);

		static void AddLight(Light* pLight);
		static void RemoveLight(Light* pLight);

    private:
        //all the static properties are shared between instances of LitMaterial
        //note that they are all PRIVATE, we do not expose this static info to the outside world
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

		static std::vector<Light*> _lights;

		//keep track of the amount of lights
		static int _lightCount;

        //this one is unique per instance of color material
        glm::vec3 _diffuseColor;
		glm::vec3 _ambientColor;
		glm::vec3 _specularColor;

		int _shininess = 4;

		bool _overrideSpecularLight = false;
};

#endif // LITMATERIAL_HPP
