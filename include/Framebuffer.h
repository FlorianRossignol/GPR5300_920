#pragma once
#include <iostream>
#include <gl/glew.h>

namespace gpr5300
{
	class Framebuffer
	{
	public:
		void Init();
		void BindFrameBuffer();
		void BindDefaultBuffer();
		void CreateScreenVao();
	private:
		GLuint fbo_;
		GLuint texture_;
		GLuint rbo_{}, vbo_{},vao_{};

		float quadVertices[4 * 6] = {
			// positions   // texCoords
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};
		
	};
}