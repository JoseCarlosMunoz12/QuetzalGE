#version 440

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;
in float visibility;

out vec4 fs_color;

uniform sampler2D Texture0;

void main()
{
	vec3 col = texture(Texture0,vs_texcoord).rgb;
	fs_color = vec4(col,1.0);
}
