#include "Macros.h"


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall()
{
    if (GLenum error = glGetError())
    {
        std::cout << "glError: " << error << std::endl;
        return false;
    }
    return true;
}


