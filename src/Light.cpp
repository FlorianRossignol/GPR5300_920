#include "Light.h"


namespace gpr5300
{
	void Light::SetVao()
	{
		glGenVertexArrays(1, &lightvao_);
		glBindVertexArray(lightvao_);
	}

	void Light::Draw()
	{
		glBindVertexArray(lightvao_);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
