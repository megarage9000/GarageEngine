#version 330
layout(points) in;
layout(triangle_strip, max_vertices = 5) out;

void build_house(vec4 position) {
	gl_Position = position + vec4(-0.2f, -0.2f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = position + vec4(0.2f, -0.2f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = position + vec4(-0.2f, 0.2f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = position + vec4(0.2f, 0.2f, 0.0f, 0.0f);
	EmitVertex();
	gl_Position = position + vec4(0.0f, 0.4f, 0.0f, 0.0f);
	EmitVertex();
	EndPrimitive();
}

void main() {
	build_house(gl_in[0].gl_Position);
}