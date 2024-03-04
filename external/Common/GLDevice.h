#pragma once
#include <GLConfig.h>

namespace GL{
    GLuint LoadShader(LPCSTR filename, GLenum type);

    GLuint LoadTexture(LPCSTR filename);
};