#version 440

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_texcoord;
layout (location = 2) in vec3 vertex_normal;
layout (location = 3) in ivec4 vertex_matid;
layout (location = 4) in vec4 vertex_weights;

out vec3 vs_position;
out vec2 vs_texcoord;
out vec3 vs_normal;

const int MAX_BONES = 100;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 Bones[MAX_BONES];

mat4 VerifyVal(int MatId,float Weight)
{
	if ( MatId == -1)
		return mat4(0.f);
	return Bones[MatId] * Weight;
}
void main()
{
	mat4 BoneTransform =  VerifyVal(vertex_matid.x,vertex_weights.x);
	BoneTransform += VerifyVal(vertex_matid.y,vertex_weights.y);
	BoneTransform += VerifyVal(vertex_matid.z,vertex_weights.z);
	BoneTransform += VerifyVal(vertex_matid.w,vertex_weights.w);
	if (BoneTransform == mat4(0.f))
		BoneTransform = mat4(1.f);

	vec4 GLPos = BoneTransform * vec4(vertex_position,1.f);
	vs_position = vec4(ModelMatrix * GLPos).xyz;
	vs_texcoord = vertex_texcoord;

	vec4 NormalL = BoneTransform * vec4(vertex_normal,1.f);
	vs_normal = vec4(ModelMatrix * NormalL).xyz;

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * GLPos;
}