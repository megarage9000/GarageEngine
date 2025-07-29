#version 330

/*
	We can declare what the geometry shader takes in and out. The types can be:

	- points
	- line_strip
	- line_adjacency
	- triangle_strip
	- triangle_adjaceny
*/
layout (points) in;
layout (line_strip, max_vertices = 2) out;

// We must get render primitive vertices from previous stage, and this is done by a built in variable
// gl_in, which is an array that looks like this:

/* in gl_Vertex
{
    vec4  gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
} gl_in[];  
*/

void main() {
	gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
	// Calling this adds the gl_Position to the current primitive
	EmitVertex();

	gl_Position = gl_in[0].gl_Position +  vec4(0.1, 0.0, 0.0, 0.0);
	EmitVertex();

	// Calling this combines all the vertices from the EmitVertex() calls into one primitive
	EndPrimitive();
}