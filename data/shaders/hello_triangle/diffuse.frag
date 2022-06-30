#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 textCoord;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 ambient;
uniform vec3 objectColor;
uniform sampler2D ourTexture;

void main()
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float Diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = Diff * lightColor;

	vec3 result = (ambient*0.1 + diffuse) * objectColor;
	FragColor = vec4(result,1.0) * texture(ourTexture,textCoord);
}