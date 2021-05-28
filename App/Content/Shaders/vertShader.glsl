#version 430

in vec3 v_vertex;

void main(void) 
{ 
    gl_Position = vec4(v_vertex, 1.0f); 
}