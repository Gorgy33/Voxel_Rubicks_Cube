#version 440 core
layout (depth_any) out float gl_FragDepth;
uniform vec3 color;

in VERTEX_OUT
{
    float depth;
    vec3 normal;
} fragIn;
void main()
{
//    gl_FragColor = vec4(color, 1.0) * (
//                0.3f + abs(dot(fragIn.normal, vec3(1.0, 1.0, 1.0))) * 0.8f);
    gl_FragDepth = fragIn.depth;
//    vec3 depth = vec3(fragIn.depth);
//    gl_FragColor = vec4(depth, 1.0);
    gl_FragColor = vec4(fragIn.normal, 1.0);
}
