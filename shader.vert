#version 440 core
layout(location = 0) in vec3 position;

out float depth;
out VERTEX_OUT
{
    float depth;
} vertexOut;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

void main()
{
    gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(position, 1.0);
    vertexOut.depth = (gl_Position.z - 0.1) / 100.0;
}
