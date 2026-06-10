#version 430

layout(location = 0) in vec3 aPos;

out VS_OUT
{
    vec3 worldPos;
} vs_out;

void main()
{
    vs_out.worldPos = aPos;
}