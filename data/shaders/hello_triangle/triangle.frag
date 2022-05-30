#version 310 es
precision highp float;

in vec2 texCoord;

layout(location = 0) out vec4 fragColor;

uniform sampler2D ourTexture;


void main() {
    fragColor = texture(ourTexture,texCoord);
}