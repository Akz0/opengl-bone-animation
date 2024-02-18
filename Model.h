#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H
#include "Mesh.h"


#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <tuple>
#include <map>

struct BoneInfo
{
	int ID;
	glm::mat4 Offset;
};


class Model
{
public:

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0f);

	std::vector <Mesh> meshes;
	std::vector<Vertex> vertices;
	std::vector <GLuint> indices;


	std::map<std::string, BoneInfo> m_BoneInfoMap;
	int m_BoneCounter = 0;

	auto& GetBoneInfoMap() { return m_BoneInfoMap; }
	int& GetBoneCount() { return m_BoneCounter; }


	
	std::vector<std::vector<Texture>> textures;

	Model(const char* filePath, std::vector<std::vector <Texture>>& textures);
	void ProcessNode(aiNode* node, const aiScene* scene, int currentNode, std::vector<std::vector <Texture>>& textures);
	
	void Draw(Shader& ShaderProgram, Camera& camera);
	void UpdateCamera(Shader& ShaderProgram, Camera& camera);
	void UpdateLight(Shader &ShaderProgram, glm::vec4 lightColor, glm::vec3 lightPosition);
private:
	std::pair<std::vector<Vertex>, std::vector<GLuint>> ProcessMesh(const aiMesh* mesh);
};

#endif // !MODEL_CLASS_H
