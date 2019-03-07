#include "glm.hpp"

#include "TextureMaterial.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "ThirdPerson/config.hpp"

ShaderProgram* LitTextureMaterial::_shader = NULL;

GLint LitTextureMaterial::_uMVPMatrix = 0;
GLint LitTextureMaterial::_uDiffuseTexture = 0;

GLint LitTextureMaterial::_aVertex = 0;
GLint LitTextureMaterial::_aNormal = 0;
GLint LitTextureMaterial::_aUV = 0;

LitTextureMaterial::LitTextureMaterial(Texture * pDiffuseTexture, glm::vec3 pSpecularColor) :_diffuseTexture(pDiffuseTexture), _specularColor(pSpecularColor)
{
	_lazyInitializeShader();
}

LitTextureMaterial::~LitTextureMaterial() {}

void LitTextureMaterial::_lazyInitializeShader()
{
	if (!_shader) 
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::THIRDPERSON_SHADER_PATH + "litTexture.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::THIRDPERSON_SHADER_PATH + "litTexture.fs");
		_shader->finalize();

		//cache all the uniform and attribute indexes
		_uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
		_uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");

		_aVertex = _shader->getAttribLocation("vertex");
		_aNormal = _shader->getAttribLocation("normal");
		_aUV = _shader->getAttribLocation("uv");
	}
}

void LitTextureMaterial::setDiffuseTexture(Texture* pDiffuseTexture)
{
	_diffuseTexture = pDiffuseTexture;
}

void LitTextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	if (!_diffuseTexture) return;

	_shader->use();

	//Print the number of lights in the scene and the position of the first light.
	//It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
	//if (pWorld->getLightCount() > 0) {
	//    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
	//}

	//setup texture slot 0
	glActiveTexture(GL_TEXTURE0);
	//bind the texture to the current active slot
	glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
	//tell the shader the texture slot for the diffuse texture is slot 0
	glUniform1i(_uDiffuseTexture, 0);

	/**/
	//set the material color
	glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));
	glUniform1i(_shader->getUniformLocation("shininess"), _shininess);
	glUniform1i(_shader->getUniformLocation("lightCount"), LitMaterial::GetLightCount());


	glm::vec3 specularColor = _specularColor;

	std::vector<Light*> _lights = LitMaterial::getLights();

	//pass in the light properties
	for (size_t i = 0; i < _lights.size(); i++)
	{
		if (!_overrideSpecularLight)
		{
			specularColor = _lights[i]->GetColor();
		}

		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].specularColor"), 1, glm::value_ptr(specularColor));

		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightColor"), 1, glm::value_ptr(_lights[i]->GetColor()));
		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].ambientLightColor"), 1, glm::value_ptr(_lights[i]->GetAmbientColor()));
		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightPosition"), 1, glm::value_ptr(_lights[i]->GetPosition()));
		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightForward"), 1, glm::value_ptr(_lights[i]->GetForwardDirection()));
		glUniform1i(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightType"), _lights[i]->GetType());

		//spotLight properties
		if (_lights[i]->GetType() == LightType::SPOT)
		{
			glUniform1f(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].coneAngle"), _lights[i]->GetConeAngle());
			glUniform1f(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].fallOffAngle"), _lights[i]->GetFallOffAngle());
		}
	}

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));
	/**/

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
