#pragma once

#undef UNICODE
#undef _UNICODE

#include <GLExtension.h>
#include <iostream>

#pragma warning(disable : 5082)

#define log_error(x,...) __error(x, __FILE__ , __LINE__, __VA_ARGS__)

inline void __error(const char* code, const char* filename, int line, ...)
{
    va_list args;
    va_start(args, code);
    char codeBuffer[256]{};

    vsnprintf_s(codeBuffer, -1, code, args);

    filename = (::strrchr(filename, '\\') + 1);

    char totalBuffer[256]{};

    sprintf_s(totalBuffer, "file : %s\nline : %d\n\n%s\n", filename, line, codeBuffer);
    va_end(args);

    int res = MessageBoxA(NULL, totalBuffer, "Error", MB_OK | MB_ICONWARNING);
    if (res == IDOK)
    {
        ExitProcess(0);
    }
};

#define log std::cout
#define endl std::endl

//#include "cmake_source_dir.h"
//#define CMAKE_SOURCE_DIR cmake_source_dir

