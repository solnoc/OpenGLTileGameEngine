#include "error_checking.h"

#include <iostream>

void GLClearErrors()
{
    while (glGetError() != GL_NO_ERROR);
}
bool GLlogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "OPENGL ERROR in file : " << file << " ,in function : " << function << " ,on line : " << line <<
            " ,with error code: " << error << std::endl;
        return false;
    }
    return true;
}
