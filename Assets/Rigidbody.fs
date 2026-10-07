#version 330 core

out vec4 color;

in vec4 RGBA;

void main()
{
    color = RGBA;
}