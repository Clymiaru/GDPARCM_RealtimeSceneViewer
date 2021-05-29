#version 430

in vec3 vertexColor;
out vec4 fragColor;

void main(void)
{
    vec3 color = 1 - vertexColor - 0.5;

    fragColor = vec4(color, 1.0);
}