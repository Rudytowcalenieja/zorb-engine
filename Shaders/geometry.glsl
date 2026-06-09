#version 430
layout (points) in;
layout (points, max_vertices = 4) out;

void create_face(vec4 position) {
	gl_Position = position + vec4(-0.5, -0.5, 0.0, 0.0);
	EmitVertex();
	gl_Position = position + vec4(-0.5,  0.5, 0.0, 0.0);
	EmitVertex();
	gl_Position = position + vec4( 0.5, -0.5, 0.0, 0.0);
	EmitVertex();
	gl_Position = position + vec4( 0.5,  0.5, 0.0, 0.0);
	EmitVertex();
	EndPrimitive();
	cross()
}

void main() {
	create_face(gl_in[0].gl_Position);
}