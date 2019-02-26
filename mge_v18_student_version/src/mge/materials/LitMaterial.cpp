#include "glm.hpp"

#include "mge/materials/LitMaterial.hpp"
#include "ThirdPerson/config.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/ShaderProgram.hpp"

ShaderProgram* LitMaterial::_shader = NULL;
int LitMaterial::_lightCount = 0;
std::vector<Light*> LitMaterial::_lights = std::vector<Light*>();

LitMaterial::LitMaterial(glm::vec3 pDiffuseColor, glm::vec3 pSpecularColor) :_diffuseColor(pDiffuseColor), _specularColor(pSpecularColor)
{
	//every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
	_lazyInitializeShader();
}

void LitMaterial::_lazyInitializeShader()
{
	//this shader contains everything the material can do (it can render something in 3d using a single color)
	if (!_shader)
	{
		_shader = new ShaderProgram();
		_shader->addShader(GL_VERTEX_SHADER, config::THIRDPERSON_SHADER_PATH + "lit.vs");
		_shader->addShader(GL_FRAGMENT_SHADER, config::THIRDPERSON_SHADER_PATH + "lit.fs");
		_shader->finalize();
	}
}

LitMaterial::~LitMaterial()
{
	//dtor
}

void LitMaterial::setDiffuseColor(glm::vec3 pDiffuseColor)
{
	_diffuseColor = pDiffuseColor;
}

void LitMaterial::setAmbientColor(glm::vec3 pAmbientColor)
{
	_ambientColor = pAmbientColor;
}

void LitMaterial::setSpecularColor(glm::vec3 pSpecularColor)
{
	_specularColor = pSpecularColor;
}

void LitMaterial::setShininess(int pShininess)
{
	_shininess = pShininess;
}

void LitMaterial::AddLight(Light* pLight)
{
	LitMaterial::_lights.push_back(pLight);
	LitMaterial::_lightCount++;
}

void LitMaterial::RemoveLight(Light* pLight)
{
	std::vector<Light*>::iterator itr;
	std::vector<Light*>::iterator end = LitMaterial::_lights.end();

	for (itr = LitMaterial::_lights.begin(); itr != end; itr++)
	{
		if (*itr == pLight)
		{
			LitMaterial::_lights.erase(itr);
			break;
		}
	}
}

int LitMaterial::GetLightCount()
{
	return LitMaterial::_lightCount;
}

std::vector<Light*> LitMaterial::getLights()
{
	return _lights;
}


void LitMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix)
{
	_shader->use();
	//set the material color
	glUniform3fv(_shader->getUniformLocation("diffuseColor"), 1, glm::value_ptr(_diffuseColor));
	glUniform1i(_shader->getUniformLocation("shininess"), _shininess);
	glUniform1i(_shader->getUniformLocation("lightCount"), LitMaterial::_lightCount);


	glm::vec3 specularColor = _specularColor;

	//pass in the light properties
	for (int i = 0; i < LitMaterial::_lights.size(); i++)
	{
		if (!_overrideSpecularLight)
		{
			specularColor = LitMaterial::_lights[i]->GetColor();
		}

		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].specularColor"), 1, glm::value_ptr(specularColor));

		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightColor"), 1, glm::value_ptr(LitMaterial::_lights[i]->GetColor()));
		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].ambientLightColor"), 1, glm::value_ptr(LitMaterial::_lights[i]->GetAmbientColor()));
		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightPosition"), 1, glm::value_ptr(LitMaterial::_lights[i]->GetPosition()));
		glUniform3fv(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightForward"), 1, glm::value_ptr(LitMaterial::_lights[i]->GetForwardDirection()));
		glUniform1i(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].lightType"), LitMaterial::_lights[i]->GetType());

		//spotLight properties
		if (LitMaterial::_lights[i]->GetType() == LightType::SPOT)
		{
			glUniform1f(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].coneAngle"), LitMaterial::_lights[i]->GetConeAngle());
			glUniform1f(_shader->getUniformLocation("Lights[" + std::to_string(i) + "].fallOffAngle"), LitMaterial::_lights[i]->GetFallOffAngle());
		}
	}

	//pass in all MVP matrices separately
	glUniformMatrix4fv(_shader->getUniformLocation("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(pViewMatrix));
	glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));

	//now inform mesh of where to stream its data
	pMesh->streamToOpenGL(
		_shader->getAttribLocation("vertex"),
		_shader->getAttribLocation("normal"),
		_shader->getAttribLocation("uv")
	);


}
