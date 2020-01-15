#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normal;
layout(location = 2) in vec2 v_coord;
layout(location = 1) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Clock;

// TODO: output values to fragment shader
out vec2 frag_coord;
out vec3 frag_normal;
out vec3 frag_color;
out vec3 frag_position;

void main()
{
	// TODO: send output to fragment shader
	mat4 rotate = transpose(mat4(
			cos(Clock), 0, (-1) * sin(Clock), 0,
			0, 1, 0, 0,
			sin(Clock), 0, cos(Clock), 0,
			0, 0, 0, 1));
	frag_position = v_position;
	frag_normal = v_normal;
	frag_color = v_color * (1 - abs(sin (Clock)));
	frag_coord = v_coord;
	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * rotate * vec4(v_position, 1.0);
}
