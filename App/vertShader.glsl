#version 430

in vec3 v_vertex;
in vec3 v_color;

out vec3 f_color;

void main(void) {
	gl_Position = vec4(v_vertex, 1.0f);
	f_color = v_color;
}