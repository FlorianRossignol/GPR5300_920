#include "MeshModel.h"

#include <string>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

namespace gpr5300
{
		float verticesc[72] = {
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

		unsigned int indicesc[36] = {
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

		float textCoordsc[48] = {
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

		float normalc[72] = {
			//front
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,

			//back
			0.0f,  0.0f,  1.0f,
			0.0f,  0.0f,  1.0f,
			0.0f,  0.0f,  1.0f,
			0.0f,  0.0f,  1.0f,

			//right
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			//left
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			//top
			0.0f, 1.0f,  0.0f,
			0.0f, 1.0f,  0.0f,
			0.0f, 1.0f,  0.0f,
			0.0f, 1.0f,  0.0f,

			//bottom
			0.0f,  -1.0f,  0.0f,
			0.0f,  -1.0f,  0.0f,
			0.0f,  -1.0f,  0.0f,
			0.0f,  -1.0f,  0.0f,
	
		};


		MeshModel::MeshModel(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures)
		{
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;

			SetupMesh();
		}

	void MeshBasic::init()
	{
		//vao
		glGenVertexArrays(1, &vao_);
		glBindVertexArray(vao_);

		//vbo
		glGenBuffers(1, &vbo_[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesc), verticesc, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//bind shader coord data vbo2	
		glGenBuffers(1, &vbo_[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textCoordsc), textCoordsc, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		
		//ebo
		glGenBuffers(1, &ebo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesc), indicesc, GL_STATIC_DRAW);
	}

	void MeshBasic::initDiffuse()
	{
		//vao
		glGenVertexArrays(1, &vao_);
		glBindVertexArray(vao_);

		//vbo
		glGenBuffers(1, &vbo_[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesc), verticesc, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//bind shader coord data vbo2	
		glGenBuffers(1, &vbo_[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textCoordsc), textCoordsc, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		//bindnormal

		glGenBuffers(1, &vbo_[2]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(normalc), &normalc, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);


		//ebo
		glGenBuffers(1, &ebo_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesc), indicesc, GL_STATIC_DRAW);
	}

	void MeshModel::Draw(Shader& shader)
	{
		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to string
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to string
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to string

			// now set the sampler to the correct texture unit
			_shader.SetInt(("material" + name + number).c_str(), i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		// draw mesh
		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}

	void MeshBasic::Draw()
	{
		glBindVertexArray(vao_);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	}

	void MeshBasic::Deleted()
	{
		glDeleteVertexArrays(1, &vao_);
	}

	void MeshModel::SetupMesh()
	{
		glGenVertexArrays(1, &_vao);
		glGenBuffers(1, &_vbo);
		glGenBuffers(1, &_ebo);

		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TextCoords));
		// vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		// vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

			glBindVertexArray(0);
	}
}
