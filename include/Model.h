#pragma once
#include <iostream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "MeshModel.h"

namespace gpr5300
{
	class Model
	{
	public:
		Model();

		void Draw(Shader &shader);
		void Load(std::string_view path);

	private:

		std::vector<MeshModel> _meshes;
		std::string _directory;
		std::vector<MeshModel::Texture> textures_load;

		void LoadModel(std::string_view path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		
		MeshModel ProcesseMesh(aiMesh* mesh, const aiScene* scene);
		unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
		std::vector<MeshModel::Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string_view typeName);
	};

}
