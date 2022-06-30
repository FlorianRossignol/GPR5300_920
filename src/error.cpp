//
// Created by efarhan on 6/5/21.
//
#include "error.h"
#include <GL/glew.h>
#include <fmt/core.h>


namespace gpr5300
{

void CheckError(std::string_view file, int line)
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        // Process/log the error.
        switch (err)
        {
            case GL_INVALID_ENUM:
                fmt::print("File: {} Line: {} OpenGL: GL_INVALID_ENUM \n", file, line);
                break;
            case GL_INVALID_VALUE:
                fmt::print("File: {} Line: {} OpenGL: GL_INVALID_VALUE \n", file, line);
                break;
            case GL_INVALID_OPERATION:
               fmt::print("File: {} Line: {} OpenGL: GL_INVALID_OPERATION \n", file, line);
                break;
            case GL_STACK_OVERFLOW:
               fmt::print("File: {} Line: {} OpenGL: GL_STACK_OVERFLOW \n", file, line);
                break;
            case GL_STACK_UNDERFLOW:
               fmt::print("File: {} Line: {} OpenGL: GL_STACK_UNDERFLOW \n", file, line);
                break;
            case GL_OUT_OF_MEMORY:
                fmt::print("File: {} Line: {} OpenGL: GL_OUT_OF_MEMORY \n", file, line);
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                fmt::print("File: {} Line: {} OpenGL: GL_INVALID_FRAMEBUFFER_OPERATION \n", file, line);
                break;
            case GL_CONTEXT_LOST:
                fmt::print("File: {} Line: {} OpenGL: GL_CONTEXT_LOST \n", file, line);
                break;
            case GL_TABLE_TOO_LARGE:
                fmt::print("File: {} Line: {} OpenGL: GL_TABLE_TOO_LARGE \n", file, line);
                break;
            default:
                break;
        }
    }
}
}