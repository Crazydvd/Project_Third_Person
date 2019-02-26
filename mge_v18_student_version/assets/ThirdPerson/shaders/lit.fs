//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform mat4 viewMatrix;

//uniform vec3 ambientLightColor;
uniform vec3 diffuseColor;
//uniform vec3 specularColor;

//uniform vec3 lightPosition;
//uniform vec3 lightForward;
//uniform vec3 lightColor;
//uniform int lightType;

//uniform float coneAngle;
//uniform float fallOffAngle;

uniform int lightCount;
uniform int shininess;

in vec3 worldNormal;
in vec3 position;

out vec4 fragment_color;


struct Light
{
	vec3 lightColor;
	vec3 ambientLightColor;
	vec3 specularColor;
 
	vec3 lightPosition;
	vec3 lightForward;
	int lightType;
	
	float coneAngle;
	float fallOffAngle;
 };
 
//array to store all lights
uniform Light Lights[99];


//global variables
float Intensity;
float Attenuation;
vec3 LightVector;
mat4 Cameramatrix;
vec3 CameraPosition;

//Light properties
vec3 lightColor;
vec3 ambientLightColor;
vec3 specularColor;
 
vec3 lightPosition;
vec3 lightForward;
int lightType;
	
float coneAngle;
float fallOffAngle;

//Functions
vec3 getAmbientTerm();
vec3 getDiffuseTerm();
vec3 getSpecularTerm();
vec3 calculateColor();


void main(void) 
{
	vec3 color = vec3(0, 0, 0);
	Cameramatrix = inverse(viewMatrix);
	CameraPosition = vec3(Cameramatrix[3]);
	
	for (int i = 0; i < lightCount; i++)
	{
		Intensity = 1;
		
		lightColor = Lights[i].lightColor;
		ambientLightColor = Lights[i].ambientLightColor;
		specularColor = Lights[i].specularColor;
		
		lightPosition = Lights[i].lightPosition;
		lightForward = Lights[i].lightForward;
		lightType = Lights[i].lightType;
		
		coneAngle = Lights[i].coneAngle;
		fallOffAngle = Lights[i].fallOffAngle;
		
		color += calculateColor();
	}
	
	fragment_color = vec4(color, 1);
}

vec3 getAmbientTerm()
{
	return ambientLightColor * diffuseColor;
}

vec3 getDiffuseTerm()
{	
	switch(lightType)
	{
		case 1: //directional
		LightVector = normalize(lightForward);
		break;
		
		case 2: //point
		LightVector = position - lightPosition;
		break;
		
		case 3: //spot
		LightVector = position - lightPosition;
		vec3 normalizedLight = normalize(LightVector);
		vec3 forward = normalize(lightForward);
		
		float dotProduct = dot(forward, normalizedLight);
		float angle = acos(dotProduct);
		float angleDegrees = degrees(angle);
		
		if (angleDegrees > coneAngle)
		{
			Intensity = 0;
		}
		else
		if (angleDegrees > fallOffAngle)
		{
			Intensity -= (angleDegrees - fallOffAngle) / (coneAngle - fallOffAngle);
		}
		break;
	}		
	
	float diffuseIntensity = max(dot(-normalize(LightVector), normalize(worldNormal)), 0);
	
	float distance = length(LightVector);
	float squareDistance = distance * distance;
	float c1 = 1;
	float c2 = 1;
	float c3 = 0;
	Attenuation = (c1 + c2 * distance + c3 * squareDistance);
	diffuseIntensity /= Attenuation;
	
	return diffuseIntensity * lightColor * diffuseColor;
}

vec3 getSpecularTerm()
{
	vec3 cameraVector = CameraPosition - position;
	
	vec3 lightDirection = normalize(LightVector);
	vec3 reflectedRay = reflect(lightDirection, normalize(worldNormal));
	
	float projection = dot(reflectedRay, normalize(cameraVector));
	float maximum = max(projection, 0);
	
	vec3 specularTerm = pow(maximum, shininess) * lightColor * specularColor;
	specularTerm /= Attenuation;
	
	return specularTerm;
}

vec3 calculateColor()
{
	vec3 ambientTerm = getAmbientTerm();
	
	if (lightType == 0) //ambient
	{
		return ambientTerm;
	}
	
	vec3 diffuseTerm = getDiffuseTerm();
	vec3 specularTerm = getSpecularTerm();
	
	return (ambientTerm + diffuseTerm + specularTerm) * Intensity;
}
