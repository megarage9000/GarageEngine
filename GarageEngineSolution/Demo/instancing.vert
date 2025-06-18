#version 410

layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 color;

out vec3 fColor;

uniform vec2 offsets[100];

void main() {

	// We are using instance IDs to identify instances!
	vec2 offset = offsets[gl_InstanceID];

	// Adding offset to the original position, for instancing
	gl_Position = vec4(pos + offset, 0.0, 1.0);
	fColor = color;
}

