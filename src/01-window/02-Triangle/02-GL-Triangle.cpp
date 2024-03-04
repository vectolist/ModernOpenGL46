#include <GLWindow.h>
#include <GLDevice.h>

int main(int args, char* argv[])
{
    GLWindow* window = GLCreateWindow(860, 640, "Triangle");

    RECT rc{};
    GetClientRect(window->mHwnd, &rc);
    glViewport(0,0, rc.right - rc.left, rc.bottom - rc.top);

    float v = 0.5;
    float vertices[] = {
        -v,-v,0,
        0, v, 0,
        v, -v, 0
    };

    GLuint vbo, vao;
    glCreateBuffers(1, &vbo);
    glNamedBufferStorage(vbo, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &vao);
    //glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float) * 3);

    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);

    LPCSTR vsCode = R"(
        #version 460 
        layout(location = 0) in vec3 pos;

        out gl_PerVertex {
            vec4 gl_Position;
            float gl_PointSize;
        };

        void main()
        {
            gl_Position = vec4(pos, 1);
        };

    )";



    GLuint vs = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vsCode);

    GLint status;
    glProgramParameteri(vs, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glGetProgramiv(vs, GL_LINK_STATUS, &status);

    if(status == GL_FALSE){
        char err[128];
        glGetProgramInfoLog(vs, 128, nullptr, err);
        glDeleteShader(vs);
        MessageBoxA(NULL, err, "shader error", MB_OK);
    }

        LPCSTR psCode = R"(
        #version 460 core

        out vec4 outColor;

        void main()
        {
            outColor = vec4(1,1,0, 1);
        };
    )";

    GLuint ps = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &psCode);

    status = 0;
    glProgramParameteri(ps, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glGetProgramiv(ps, GL_LINK_STATUS, &status);

    if(status == GL_FALSE){
        char err[128];
        glGetProgramInfoLog(ps, 128, nullptr, err);
        glDeleteShader(ps);
        MessageBoxA(NULL, err, "shader error", MB_OK);
    }

    GLuint pipeline;
    glCreateProgramPipelines(1, &pipeline);
    glUseProgramStages(pipeline, GL_VERTEX_SHADER_BIT, vs);
    glUseProgramStages(pipeline, GL_FRAGMENT_SHADER_BIT, ps);

    glBindProgramPipeline(pipeline);
    glBindVertexArray(vao);

    

    while (GLBeginFrame(window))
    {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f,0.2f,0.2f,1.f);

        
        glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float) * 3);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        GLSwapBuffers(window);

    }
    
    return 0;
}