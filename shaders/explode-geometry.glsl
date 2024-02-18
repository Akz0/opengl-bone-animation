#version 330 core

layout (triangles) in;
layout (triangle_strip,max_vertices = 3) out;

out vec3 CurrentPosition;
out vec3 Normal;
out vec3 Color;
out vec2 TexCord;

in DATA
{
	vec3 CurrentPosition;
	vec3 Normal;
	vec3 Color;
	vec2 TexCord;
	mat4 CameraMatrix;
} data_in[];


void main(){
	
	gl_Position = data_in[0].CameraMatrix * (gl_in[0].gl_Position);
	CurrentPosition = data_in[0].CurrentPosition;
	Normal = data_in[0].Normal;
	Color = data_in[0].Color;
	TexCord = data_in[0].TexCord;
	EmitVertex();

	gl_Position = data_in[1].CameraMatrix * (gl_in[1].gl_Position);
	CurrentPosition = data_in[1].CurrentPosition;
	Normal = data_in[1].Normal;
	Color = data_in[1].Color;
	TexCord = data_in[1].TexCord;
	EmitVertex();

	
	gl_Position = data_in[2].CameraMatrix * (gl_in[2].gl_Position);
	CurrentPosition = data_in[2].CurrentPosition;
	Normal = data_in[2].Normal;
	Color = data_in[2].Color;
	TexCord = data_in[2].TexCord;
	EmitVertex();

	EndPrimitive();
}


