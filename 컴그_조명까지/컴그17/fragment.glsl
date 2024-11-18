#version 330 core
in vec4 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform vec3 lightPos; //--- 조명의 위치
uniform vec3 viewPos;
uniform vec3 lightColor; //--- 조명의 색
uniform vec3 objectColor; //--- 객체의 색

void main ()
{
	float ambientLight = 0.3;
	vec3 ambient = ambientLight * lightColor;

	vec3 normalVector = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos.xyz);
	float diffuseLight = max(dot(normalVector, lightDir), 0.0);
	vec3 diffuse = diffuseLight * lightColor;

	int shininess = 128;
	vec3 viewDir = normalize(viewPos - FragPos.xyz);
	vec3 reflectDir = reflect(-lightDir, normalVector);
	float specularLight = max(dot(viewDir, reflectDir), 0.0);
	specularLight = pow(specularLight, shininess);
	vec3 specular = specularLight * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;

	FragColor = vec4(result, 1.0);
}