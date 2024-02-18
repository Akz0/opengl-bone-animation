#include "Model.h"
void CountNodes(const aiNode* node, unsigned int& count) {
	count++; // Increment count for the current node

	// Recursively count nodes for each child
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		CountNodes(node->mChildren[i], count);
	}
}

Model::Model(const char* filePath, std::vector<std::vector <Texture>>& textures) {
	std::cout << "In the Function" << std::endl;
	// Load the model
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	
	unsigned int totalNodes = 0;

	CountNodes(scene->mRootNode, totalNodes);
	std::cout << "Total number of nodes in the scene: " << totalNodes << std::endl;
	std::cout << "Total number of Bones: " << scene->mMeshes[1]->mNumBones<< std::endl;


	ProcessNode(scene->mRootNode, scene, 1,textures);
}



void Model::ProcessNode(aiNode* node, const aiScene* scene, int currentNode ,std::vector<std::vector <Texture>>& textures)
{	
	std::cout << "\n\nCurrent Node : "<< currentNode <<std::endl;
	
	for (unsigned int meshIndex = 0; meshIndex < node->mNumMeshes; meshIndex++) {
		const aiMesh* mesh = scene->mMeshes[node->mMeshes[meshIndex]];
		std::cout << "Mesh : " << meshIndex + 1;
		auto result = ProcessMesh(mesh);
		vertices = result.first;
		indices = result.second;
		std::cout << "Mesh Loaded" << std::endl;
		std::cout << "Mesh Index" << meshIndex;
		meshes.push_back(Mesh(vertices, indices, textures[meshIndex]));
	}
	

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{	
		std::cout << "\n\nCurrent Child" << node->mNumChildren;
		ProcessNode(node->mChildren[i], scene, currentNode+1,textures);
	}
}

void SetVertexBoneDataToDefault(Vertex& vertex)
{
	for (int i = 0; i < MAX_BONE_WEIGHTS; i++)
	{
		vertex.m_BoneIDs[i] = -1;
		vertex.m_Weights[i] = 0.0f;
	}
}

std::pair<std::vector<Vertex>, std::vector<GLuint>> Model::ProcessMesh(const aiMesh* mesh) {
	// Vector to store unique vertices
	std::vector<Vertex> uniqueVertices;
	// Vector to store indices
	std::vector<unsigned int> indices;
	// Iterate over each face in the mesh
	for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
		const aiFace& face = mesh->mFaces[faceIndex];

		// Add indices for each vertex in the face
		for (unsigned int index = 0; index < face.mNumIndices; ++index) {
			unsigned int vertexIndex = face.mIndices[index];
			Vertex currentVertex;
			SetVertexBoneDataToDefault(currentVertex);
			currentVertex.position = glm::vec3(mesh->mVertices[vertexIndex].x, mesh->mVertices[vertexIndex].y, mesh->mVertices[vertexIndex].z);
			currentVertex.normal = glm::vec3(mesh->mNormals[vertexIndex].x, mesh->mNormals[vertexIndex].y, mesh->mNormals[vertexIndex].z);
			currentVertex.texUV = glm::vec2(mesh->mTextureCoords[0][vertexIndex].x, mesh->mTextureCoords[0][vertexIndex].y);
			currentVertex.tangent = glm::vec3(mesh->mTangents[vertexIndex].x, mesh->mTangents[vertexIndex].y, mesh->mTangents[vertexIndex].z);
			currentVertex.biTangent = glm::vec3(mesh->mBitangents[vertexIndex].x, mesh->mBitangents[vertexIndex].y, mesh->mBitangents[vertexIndex].z);

			// Check if the vertex with the same position, normal, and texture UV is already in uniqueVertices
			auto key = std::make_tuple(currentVertex.position, currentVertex.normal, currentVertex.texUV);
			auto it = std::find_if(uniqueVertices.begin(), uniqueVertices.end(),
				[&key](const Vertex& v) {
					return std::tie(v.position, v.normal, v.texUV) == key;
				});

			// If not found, add it to uniqueVertices
			if (it == uniqueVertices.end()) {
				uniqueVertices.push_back(currentVertex);
				indices.push_back(static_cast<unsigned int>(uniqueVertices.size() - 1));
			}
			else {
				// If found, use the existing index
				indices.push_back(static_cast<unsigned int>(std::distance(uniqueVertices.begin(), it)));
			}
		}
	}

	std::cout << "\t Unique Vertices: " << uniqueVertices.size();
	std::cout << "\t Indices: " << indices.size() << std::endl;

	return std::make_pair(uniqueVertices, indices);
}

void Model::UpdateCamera(Shader& ShaderProgram, Camera& camera) {
	ShaderProgram.Activate();
	glUniform3f(glGetUniformLocation(ShaderProgram.ID, "CameraPosition"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	camera.Matrix(ShaderProgram, "CameraMatrix");
}

void Model::UpdateLight(Shader& ShaderProgram, glm::vec4 lightColor,glm::vec3 lightPosition) {
	ShaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(ShaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(ShaderProgram.ID, "lightPosition"), lightPosition.x, lightPosition.y, lightPosition.z);
}

void Model::Draw(Shader &ShaderProgram,Camera& camera) {
	for (auto it : meshes) {
		it.Draw(ShaderProgram, camera, false);
	}
}