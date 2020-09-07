#version 400 core

in vec3 color;
in vec2 texCoord;

uniform sampler2D crateTexture;

out vec4 fragColor;

void main() 
{ 
    fragColor = texture(crateTexture, texCoord) * vec4(color, 1.0f);
};