#include "Light.h"


namespace gpr5300
{
	float vertices_light[72] = {
		//Front
		-0.5f, -0.5f, -0.5f, //0
		-0.5f, 0.5f, -0.5f,
		 0.5f, 0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,

		 //Back
		 -0.5f, -0.5f, 0.5f, //4
		 -0.5f, 0.5f, 0.5f,
		  0.5f, 0.5f, 0.5f,
		  0.5f, -0.5f, 0.5f,

		  //Right
		  0.5f, -0.5f, -0.5f, //8
		  0.5f, 0.5f, -0.5f,
		  0.5f, 0.5f, 0.5f,
		  0.5f, -0.5f, 0.5f,

		  //Left
		  -0.5f, -0.5f, -0.5f, //12
		  -0.5f, 0.5f, -0.5f,
		  -0.5f, 0.5f, 0.5f,
		  -0.5f, -0.5f, 0.5f,

		  //Top
		  -0.5f, 0.5f, -0.5f, //16
		   0.5f, 0.5f, -0.5f,
		   0.5f, 0.5f, 0.5f,
		  -0.5f, 0.5f, 0.5f,

		  //Bottom
		  -0.5f, -0.5f, -0.5f, //20
		   0.5f, -0.5f, -0.5f,
		   0.5f, -0.5f, 0.5f,
		  -0.5f, -0.5f, 0.5f
	};

	unsigned int indices_light[36] = {
		//Front
		   0, 1, 2,
		   0, 2, 3,

		   //Back
		   5, 4, 7,
		   5, 7, 6,

		   //Right
		   10, 8, 9,
		   10, 11, 8,

		   //Left
		   12, 14, 13,
		   12, 15, 14,

		   //Top
		   16, 18, 17,
		   16, 19, 18,

		   //Bottom
		   20, 21, 22,
		   20, 22, 23
	};

	float textCoords_light[48] = {
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
	};


	void Light::SetVao()
	{
		//lightvao
		glGenVertexArrays(1, &lightvao_);
		glBindVertexArray(lightvao_);	

		//vbolight
		glGenBuffers(1, &lightvbo_[0]);
		glBindBuffer(GL_ARRAY_BUFFER, lightvbo_[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_light), vertices_light, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//ebo light
		glGenBuffers(1, &lightebo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_light), indices_light, GL_STATIC_DRAW);
	}

	void Light::SetVaoDiffuse()
	{
		//lightvao
		glGenVertexArrays(1, &lightvao_);
		glBindVertexArray(lightvao_);

		//vbolight
		glGenBuffers(1, &lightvbo_[0]);
		glBindBuffer(GL_ARRAY_BUFFER, lightvbo_[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_light), vertices_light, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//ebo light
		glGenBuffers(1, &lightebo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_light), indices_light, GL_STATIC_DRAW);
	}

	void Light::Draw()
	{
		glBindVertexArray(lightvao_);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	}

	void Light::Deleted()
	{
		glDeleteVertexArrays(1, &lightvao_);
	}
}