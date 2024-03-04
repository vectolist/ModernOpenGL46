#include "GLDevice.h"

#include <vector>

 #define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <cmake_source_dir.h>

GLuint GL::LoadShader(LPCSTR filename, GLenum type)
{
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "r");
    if(!file){
        log_error("failed to load : [%s]", filename);
    }

    fseek(file, 0, SEEK_END);
    const uint32_t len = ftell(file);

    char* buffer = (char*)calloc(len, sizeof(char));
    fseek(file, 0, SEEK_SET);
    fread_s(buffer, len, len, 1, file);
    fclose(file);

    GLuint shader =  glCreateShaderProgramv(type, 1, &buffer);
    GLint status{};

    //glGetProgramiv(shader, GL_COMPILE_STATUS, &status);

    //if (status == GL_FALSE) {
    //    char err[128];
    //    glGetProgramInfoLog(shader, 128, nullptr, err);
    //    glDeleteShader(shader);
    //    char outBuf[256];
    //    sprintf_s(outBuf, sizeof(char) * 256, "[program : %s]\n %s", filename, err);
    //    MessageBoxA(nullptr, outBuf, "Compile Error", MB_OK);
    //}

    status = {};
    glProgramParameteri(shader, GL_PROGRAM_SEPARABLE, GL_TRUE);
    glGetProgramiv(shader, GL_LINK_STATUS, &status);

    if(status == GL_FALSE){
        char err[128];
        glGetProgramInfoLog(shader, 128, nullptr, err);
        glDeleteShader(shader);
        char outBuf[256];
        sprintf_s(outBuf, sizeof(char) * 256,"[program : %s]\n %s", filename, err);
        MessageBoxA(nullptr, outBuf, "Program Error", MB_OK);
    }
    free(buffer);

    return shader;
}

#include <string>
GLuint GL::LoadTexture(LPCSTR filename)
{
    std::string fileStr(cmake_source_dir);
    fileStr.append("/").append(filename);

    int w,h,comp = 0;
    const uint8_t* byte = stbi_load(fileStr.c_str(), &w, &h, &comp, 3);
    if(!byte){
        log_error("failed to load %s", fileStr.c_str());
    }
    GLuint data;
    glCreateTextures(GL_TEXTURE_2D, 1, &data);
    glTextureParameteri(data, GL_TEXTURE_MAX_LEVEL, 0);
    glTextureParameteri(data, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(data, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureStorage2D(data, 1, GL_RGB8, w, h);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTextureSubImage2D(data, 0, 0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, byte);

    return data;
}
