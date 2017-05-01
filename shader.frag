#version 440 core
layout (depth_any) out float gl_FragDepth;
uniform vec3 color;

in VERTEX_OUT
{
    float depth;
} fragIn;
void main()
{
    gl_FragColor = vec4(color, 1.0);
    gl_FragDepth = fragIn.depth;
}
