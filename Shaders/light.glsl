#version 430

out vec4 fragment;

in vec4 color;

uniform vec3 lightColor;

void main()
{
    fragment = vec4(lightColor, 1.0);
}