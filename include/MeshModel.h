#pragma once

#include <iostream>
#include <vector>
#include <gl/glew.h>

#include "Create_texture.h"
#include "Shader.h"


namespace gpr5300
{
	class  MeshModel final
	{
	public:
		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TextCoords;
			glm::vec3 Bitangent;
			glm::vec3 Tangent;
			
		};

		struct Texture
		{
			unsigned int id;
			std::string type;
			std::string path;
		};

		MeshModel(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		
		void Draw(Shader &shader);
		

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;
	private:
		void SetupMesh();
		GLuint _vbo, _ebo,_vao;
		Shader _shader;
	};

	class MeshBasic
	{
	public:
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
