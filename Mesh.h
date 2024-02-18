#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <process.h>
#include <fstream>
#include <string>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./external packages/stb/stb_image.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"


class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indices;
	std::vector <Texture> textures;

	VAO VAO;

	Mesh(std::vector <Vertex> & vertices,std::vector <GLuint> & indices,std::vector <Texture> &textures);
	void Draw(Shader &shader, Camera &camera,bool vert);
};
#endif // !MESH_CLASS_H


