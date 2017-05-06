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
    float diffuseLighting = dot(fragIn.normal, vec3(1.0, 1.0, 1.0));
    if (diffuseLighting < 0)
        diffuseLighting = 0;
    gl_FragColor = vec4(color, 1.0) * (
                0.3f + diffuseLighting * 0.7f);
    gl_FragDepth = fragIn.depth;
}
