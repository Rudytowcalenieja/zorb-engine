#version 430

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 view;
uniform mat4 projection;

in VS_OUT
{
	vec3 worldPos;
} gs_in[];

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
	vec3 p = gs_in[0].worldPos;

	// top-left corner (front face in +Z)
	vec3 v0 = p;
	vec3 v1 = p + vec3(1.0, 0.0, 0.0);
	vec3 v2 = p + vec3(0.0,-1.0, 0.0);
	vec3 v3 = p + vec3(1.0,-1.0, 0.0);

	// correct normal
	vec3 normal = vec3(0.0, 0.0, 1.0);

	// triangle 1
	FragPos = v0;
	Normal = normal;
	TexCoord = vec2(0.0, 1.0);
	gl_Position = projection * view * vec4(v0, 1.0);
	EmitVertex();

	FragPos = v2;
	Normal = normal;
	TexCoord = vec2(0.0, 0.0);
	gl_Position = projection * view * vec4(v2, 1.0);
	EmitVertex();

	FragPos = v1;
	Normal = normal;
	TexCoord = vec2(1.0, 1.0);
	gl_Position = projection * view * vec4(v1, 1.0);
	EmitVertex();

	// triangle 2
	FragPos = v3;
	Normal = normal;
	TexCoord = vec2(1.0, 0.0);
	gl_Position = projection * view * vec4(v3, 1.0);
	EmitVertex();

	EndPrimitive();
}