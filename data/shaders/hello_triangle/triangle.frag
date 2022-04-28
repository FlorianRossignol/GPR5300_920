#version 310 es
precision highp float;

in vec2 textCoord;

layout(location = 0) out vec4 fragColor;

uniform float colorCoeff;
uniform sampler2D ourTexture;
uniform sampler2D shader_;

void main() {
    fragColor = texture(ourTexture,textCoord);
}