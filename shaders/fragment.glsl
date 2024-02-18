#version 330 core

out vec4 FragColor;

in vec3 Color;
in vec2 TexCord;
in vec3 Normal;
in vec3 CurrentPosition;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normal0;
uniform sampler2D shadowMap;
uniform samplerCube skybox;

uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 CameraPosition;

vec4 PointLight(float power){
	
	vec3 LightVector = lightPosition - CurrentPosition;
	float distance = length(LightVector);

	float a = 3.1f;
	float b = 1.2f;

	float intensity = 1.0f / (a*distance*distance + b*distance + 1.0f);
	
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - CurrentPosition);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	diffuse = max(diffuse,0.0);

	float SpecularLight = 0.5f;
	vec3 ViewDirection = normalize(CameraPosition - CurrentPosition);
	vec3 ReflectionDirection = reflect(-lightDirection, normal);

	vec3 halfway = normalize(ViewDirection + lightDirection);

	float SpecularAmount = pow(max(dot(normal,halfway),0.0f),16);
	float specular = SpecularAmount * SpecularLight;

	float ambient = 0.20f;

	return ((texture(diffuse0, TexCord) * (diffuse + ambient + intensity) + texture(specular0, TexCord).r * specular) * lightColor) * power;
}

void main()
{
	FragColor = PointLight(1.0);
}