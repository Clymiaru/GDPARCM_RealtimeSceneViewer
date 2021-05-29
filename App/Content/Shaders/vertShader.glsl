#version 430

in vec3 v_vertex;
uniform mat4 transform;
uniform mat4 view_projection;

out vec3 vertexColor;

void main(void) 
{
    vertexColor = v_vertex;
    gl_Position =  view_projection * transform * vec4(v_vertex, 1.0f);
}