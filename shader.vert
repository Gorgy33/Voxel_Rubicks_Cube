#version 440 core
layout(location = 0) in vec3 position[4];
layout(location = 1) in vec3 normal[4];

//out float depth;
out VERTEX_OUT
{
    float depth[4];
    vec3 normal[4];
} vertexOut;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

void main()
{
    for(int iter = 0; iter < 4; iter++)
    {
        gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(position[iter], 1.0);
        vertexOut.depth[iter] = (gl_Position.z - 0.1) / 100.0;
        vertexOut.normal[iter] = normal[iter];
    }
}
