#version 440

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_texcoord;

out vec2 vs_texcoord;


void main()
{
	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y);
	gl_Position =  vec4(vertex_position, 1.f);
}
