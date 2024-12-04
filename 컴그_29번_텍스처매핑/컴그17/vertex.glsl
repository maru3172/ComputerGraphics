#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec3 FragPos, Normal;
out vec2 TexCoord;

uniform mat4 model, view, projection;

void main(void)
{
	gl_Position =  projection * view * model * vec4(vPos, 1.0);
	FragPos = vec3(model * vec4(vPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * vNormal;
	TexCoord = vTexCoord;
}