#version 460 core

//layout (location = 0) in vec3 pos;
//layout (location = 1) in vec3 color;

out gl_PerVertex{
    vec4 gl_Position;
    float gl_PointSize;
};

void main()
{
    const vec3 vertice[] = {
        vec3(0.5,0,0.9),
        vec3(0.2,0,0.8),
        vec3(0.0,0,0.7)
    };
    gl_Position = vec4(vertice[gl_VertexID], 1);
    gl_PointSize = 30.f;

}