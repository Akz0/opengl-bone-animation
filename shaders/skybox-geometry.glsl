#version 330 core

layout (triangles) in;
layout (triangle_strip,max_vertices = 3) out;

out vec3 TexCord;

in DATA
{	vec3 TexCord;
	mat4 CameraMatrix;
	mat4 view;
} data_in[];


void main(){
	
	gl_Position = data_in[0].CameraMatrix * data_in[0].view * (gl_in[0].gl_Position);
	TexCord = data_in[0].TexCord;
	EmitVertex();

	gl_Position = data_in[1].CameraMatrix * data_in[1].view * (gl_in[1].gl_Position);
	TexCord = data_in[1].TexCord;
	EmitVertex();

	gl_Position = data_in[2].CameraMatrix * data_in[2].view * (gl_in[2].gl_Position);
	TexCord = data_in[2].TexCord;
	EmitVertex();


	EndPrimitive();
}


