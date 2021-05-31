#version 430

in vec3 vertexColor;
out vec4 fragColor;

void main(void)
{
    vec3 vertColor = clamp(vertexColor.rgb, vec3(0.5,0.5,0.5), vec3(1,1,1));
    vec3 normalizedVertexColor = normalize(vertColor);
    vec4 color = vec4(normalizedVertexColor, 1.0f);
    
    float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    fragColor = vec4(vec3(gray), 1.0);
}