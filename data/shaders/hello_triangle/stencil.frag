#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture1;

void main()
{    
    vec4 result = texture(texture_diffuse1 * texture1, TexCoords);
    FragColor = result;
}