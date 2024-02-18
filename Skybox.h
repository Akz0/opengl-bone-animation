#ifndef SKYBOX_CLASS_H
#define SKYBOX_CLASS_H

#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./external packages/stb/stb_image.h"
#include <string>
#include <iostream>
#include "Shader.h"
#include "Camera.h"

class Skybox
{	
private:
	float* skyboxVertices;
	unsigned int* skyboxIndices;

	std::string *CubeMapTextureFaces;
	unsigned int CubeMapTexture;
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;

	glm::mat4 view;
	glm::mat4 projection;

public:
	Skybox(float vertices[],unsigned int indices[],std::string textures[]) {
		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);
		skyboxVertices = vertices;
		skyboxIndices = indices;
		CubeMapTextureFaces = textures;
	}
	void SetupSkybox();
	void DrawSkybox(Shader& ShaderProgram,Camera &camera, float width,float height);
};

#endif // !SKYBOX_CLASS_H
