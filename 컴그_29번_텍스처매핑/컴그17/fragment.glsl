#version 330 core
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;
in vec2 TexCoord;

uniform vec3 lightPos; //--- 조명의 위치
uniform vec3 viewPos;
uniform vec3 lightColor; //--- 조명의 색
uniform vec3 objectColor; //--- 객체의 색

uniform sampler2D outTexture;

void main ()
{
   float ambientLight = 0.01;
   vec3 ambient = ambientLight * lightColor;

   vec3 normalVector = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);
   float diffuseLight = max(dot(normalVector, lightDir), 0.1);
   vec3 diffuse = diffuseLight * lightColor;

   int shininess = 128;
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, normalVector);
   float specularLight = pow(max(dot(viewDir, reflectDir), 0.1), shininess);
   vec3 specular = specularLight * lightColor;

   vec4 texColor = texture(outTexture, TexCoord);
   vec3 result = (ambient + diffuse + specular) * objectColor;
   FragColor = texColor * vec4(result, 0.2);
}