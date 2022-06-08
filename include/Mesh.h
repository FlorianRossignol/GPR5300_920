#pragma once

#include <iostream>
#include <gl/glew.h>
#include "Create_texture.h"
#include "Pipeline.h"

namespace gpr5300
{
	class Cube final
	{
	public:
		Cube();
		virtual void init();
		virtual void Draw();
		virtual void Deleted();
		
	private:
		GLuint vao_ = 0;
		GLuint vbo_[2] = {};
		GLuint ebo_ = 0;
	};
}
