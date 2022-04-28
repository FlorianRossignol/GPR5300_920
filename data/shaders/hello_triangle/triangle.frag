#version 310 es
precision highp float;

in vec3 ourColor;

layout(location = 0) out vec4 outColor;

uniform float colorCoeff;

void main() {
    outColor = vec4(ourColor * colorCoeff,1.0f);
}