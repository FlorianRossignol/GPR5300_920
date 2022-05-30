#pragma once
#include <GL/glew.h>

namespace gpr5300
{
	struct Error
	{
		GLenum glCheckError(const char* file, int line);
	};

	
}
