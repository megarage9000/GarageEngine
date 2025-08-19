
#version 330


/*

At the start of a geometry shader we need to declare the type of primitive input we're receiving from the vertex shader. 
We do this by declaring a layout specifier in front of the in keyword. This input layout qualifier can take any of the 
following primitive values:

points: when drawing GL_POINTS primitives (1).
lines: when drawing GL_LINES or GL_LINE_STRIP (2).
lines_adjacency: GL_LINES_ADJACENCY or GL_LINE_STRIP_ADJACENCY (4).
triangles: GL_TRIANGLES, GL_TRIANGLE_STRIP or GL_TRIANGLE_FAN (3).
triangles_adjacency : GL_TRIANGLES_ADJACENCY or GL_TRIANGLE_STRIP_ADJACENCY (6).

These are almost all the rendering primitives we're able to give to rendering calls like glDrawArrays. If we'd chosen to 
draw vertices as GL_TRIANGLES we should set the input qualifier to triangles. The number within the parenthesis represents the
minimal number of vertices a single primitive contains.

We also need to specify a primitive type that the geometry shader will output and we do this via a layout specifier in front of 
the out keyword. Like the input layout qualifier, the output layout qualifier can take several primitive values:

points
line_strip
triangle_strip

*/
layout(points) in;
layout(triangle_strip, max_vertices = 5) out;

// Better to pass in non attributes as interfaces!
in VS_OUT {
	vec3 color;
} gs_in[];

out vec3 fColor;

void build_house(vec4 position) {
	fColor = gs_in[0].color;
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