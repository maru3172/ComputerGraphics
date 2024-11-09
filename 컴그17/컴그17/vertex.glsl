#version 330 core
//--- in_Position: attribute index 0
//--- in_Color: attribute index 1
layout (location = 0) in vec3 vPos; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec3 in_Color; //--- �÷� ����: attribute position 1
out vec3 out_Color; //--- �����׸�Ʈ ���̴����� ����

uniform mat4 modelTransform, viewTransform, projectionTransform;

void main(void)
{
	gl_Position =  projectionTransform * viewTransform * modelTransform * vec4(vPos, 1.0);
	out_Color = in_Color;
}