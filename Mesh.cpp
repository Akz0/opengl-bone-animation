#include "Mesh.h"
Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures) {
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	VAO.Bind();

	VBO VBO1(vertices);
	EBO EBO1(indices);

	//Positions
	VAO.LinkAttributes(VBO1, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
	//Normals
	VAO.LinkAttributes(VBO1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	//Color
	VAO.LinkAttributes(VBO1, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	//TextureUV
	VAO.LinkAttributes(VBO1, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	//tangents
	VAO.LinkAttributes(VBO1, 4, 3, GL_FLOAT, sizeof(Vertex), (void*)(12 * sizeof(float)));
	//bitangent
	VAO.LinkAttributes(VBO1, 5, 3, GL_FLOAT, sizeof(Vertex), (void*)(15 * sizeof(float)));
	// ids
	VAO.LinkAttributes(VBO1, 6, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
	// weights
	VAO.LinkAttributes(VBO1, 7, 4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
	VAO.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
}


void Mesh::Draw(Shader& shader, Camera& camera,bool vert) {
	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	unsigned int numNormal = 0;


	for (unsigned int i = 0; i < textures.size(); i++) {
		std::string num;
		std::string type = textures[i].type;

		if (type == "diffuse") {
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular") {
			num = std::to_string(numSpecular++);
		}
		else if (type == "normal") {
			num = std::to_string(numNormal++);
		}

		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	glUniform3f(glGetUniformLocation(shader.ID, "CameraPosition"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "CameraMatrix");
	 
	if (vert) {
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
}