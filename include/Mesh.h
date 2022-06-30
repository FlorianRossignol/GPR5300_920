#pragma once

#include <iostream>
#include <gl/glew.h>
#include "Create_texture.h"
#include "Pipeline.h"

namespace gpr5300
{
	class Mesh final
	{
	public:
		Mesh();
		virtual void init();
		void initDiffuse();
		virtual void Draw();
		virtual void Deleted();
		
	private:
		GLuint vao_ = 0;
		GLuint vbo_[3] = {};
		GLuint ebo_ = 0;
	};
}
