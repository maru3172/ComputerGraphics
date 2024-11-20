#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
out vec3 FragPos, Normal;

uniform mat4 model, view, projection;

void main(void)
{
	gl_Position =  projection * view * model * vec4(vPos, 1.0);
	FragPos = vec3(model * vec4(vPos, 1.0));
	Normal = vNormal;
}