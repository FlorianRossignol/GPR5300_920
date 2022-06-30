#version 310 es
precision highp float;

in vec2 texCoord;

layout(location = 0) out vec4 fragColor;

uniform sampler2D ourTexture;
uniform vec3 ambient;
uniform vec3 objectColor;


void main() {

vec3 result = ambient * objectColor;
    fragColor = vec4(result, 0.0) * texture(ourTexture,texCoord);
}