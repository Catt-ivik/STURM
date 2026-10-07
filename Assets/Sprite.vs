#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoord;
out float alpha;

uniform float aAlpha;
uniform mat4 transform;
uniform mat4 projection;

void main()
{
    gl_Position = projection * transform * vec4(aPos, 0.0, 1.0);
    TexCoord = aTex;
    alpha = aAlpha;
}