#version 330 core

layout (location = 0) in vec2 aPos;

out vec4 RGBA;

uniform vec4 aRGBA;
uniform mat4 transform;
uniform mat4 projection;

void main()
{
    gl_Position = projection * transform * vec4(aPos, 0.0, 1.0);
    RGBA = aRGBA;
}