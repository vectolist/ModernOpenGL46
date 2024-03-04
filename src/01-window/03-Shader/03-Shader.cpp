#include <GLWindow.h>
#include <GLDevice.h>
#include <source_location>
#include <LinerMath.h>

int main(int args, char* argv[])
{
    auto window = GLCreateWindow(800, 600, "Shader Program");

    glEnable(GL_PROGRAM_POINT_SIZE);

    auto vs = GL::LoadShader("shader.vs", GL_VERTEX_SHADER);
    auto ps = GL::LoadShader("shader.fs", GL_FRAGMENT_SHADER);

    GLuint pipline;
    glCreateProgramPipelines(1, &pipline);

    glBindProgramPipeline(pipline);
    
    glUseProgramStages(pipline, GL_VERTEX_SHADER_BIT, vs);
    glUseProgramStages(pipline, GL_FRAGMENT_SHADER_BIT, ps);

    GLuint vao;
    glCreateVertexArrays(1, &vao);

    glBindVertexArray(vao);

    mat4f m;

    log << m << endl;

    callbacks b{
        .src =nullptr,
        .dst = nullptr
    };
    
    auto texture = GL::LoadTexture("/data/texture/ground.jpg");


    while (GLBeginFrame(window))
    {
        glClearColor(0.2f,0.2f,0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClearColor(0.2f,0.2f,0.2f, 1.f);
        if(window->cb.src){
            printf("loaded resources\n");
        }
        glBindProgramPipeline(pipline);
        glDrawArrays(GL_POINTS, 0, 3);

        GLSwapBuffers(window);
    }
    
    glDeleteProgram(vs);
    glDeleteProgram(ps);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgramPipelines(1,&pipline);
    return 0;
}