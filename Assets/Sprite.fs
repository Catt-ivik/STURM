#version 330 core

out vec4 color;

in vec2 TexCoord;
in float alpha;

uniform sampler2D image;

void main()
{
    color = texture(image, TexCoord) * vec4(1.0, 1.0, 1.0, alpha);
}