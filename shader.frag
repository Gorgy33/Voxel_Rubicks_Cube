#version 440 core
//layout (depth_any) out float gl_FragDepth;
uniform vec3 color;

in VERTEX_OUT
{
    float depth[4];
    vec3 normal[4];
} fragIn;
void main()
{
    for(int iter = 0; iter < 4; iter++)
    {
        float diffuseLighting = dot(fragIn.normal[iter], vec3(1.0, 1.0, 1.0));
        if (diffuseLighting < 0)
            diffuseLighting = 0;
        gl_FragColor = vec4(color, 1.0) * (
                    0.3f + diffuseLighting * 0.8f);
        gl_FragDepth = fragIn.depth[iter];
    }
//    vec3 depth = vec3(fragIn.depth);
//    gl_FragColor = vec4(depth, 1.0);
//    gl_FragColor = vec4(fragIn.normal, 1.0);
}
