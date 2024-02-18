#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexture;
layout (location = 4) in vec3 aTangent; 
layout (location = 5) in vec3 aBiTangent;
layout (location = 6) in ivec4 boneIds; 
layout (location = 7) in vec4 weights;

out vec3 CurrentPosition;
out vec3 Normal;
out vec3 Color;
out vec2 TexCord;

uniform mat4 CameraMatrix;
uniform mat4 model;
uniform mat4 lightProjection;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

out DATA
{
	vec3 CurrentPosition;
	vec3 Normal;
	vec3 Color;
	vec2 TexCord;
	mat4 CameraMatrix;
} data_out;


void main()
{
   CurrentPosition = vec3(model * vec4(aPos,1.0f));
   gl_Position = model * vec4(aPos,1.0f);
   
   data_out.CameraMatrix = CameraMatrix;
   data_out.CurrentPosition = CurrentPosition;
   data_out.Normal = mat3(transpose(inverse(model))) * aNormal;
   data_out.Color = aColor; 
   data_out.TexCord = aTexture;
}