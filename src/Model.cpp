#include "Model.h"
#include <stb_image.h>
namespace gpr5300
{

	Model::Model() = default;
	

	void Model::Draw(Shader& shader)
	{
		for (auto& _meshe : _meshes)
		{
			_meshe.Draw(shader);
		}
	}

	void Model::Load(std::string_view path,bool flip)
	{
		
		stbi_set_flip_vertically_on_load(flip);
		LoadModel(path.data());
	}


	void Model::LoadModel(std::string_view path)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(path.data(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cerr << "ERROR::ASSIMP" << import.GetErrorString();
			return;
		}
		_directory = path.substr(0, path.find_last_of("/"));
		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0;i < node->mNumMeshes;i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			_meshes.push_back(ProcesseMesh(mesh, scene));
		}

		for (unsigned int i = 0;i < node->mNumChildren;i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}

	}

	MeshModel Model::ProcesseMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<MeshModel::Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<MeshModel::Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices;i++)
		{
			MeshModel::Vertex vertex;
			glm::vec3 vector;

			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
			//normal
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normal = vector;
			}
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;

				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TextCoords = vec;
				//tengent
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.Tangent;
				// bitangent
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.Bitangent = vector;

			}
			else
			{
				vertex.TextCoords = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(vertex);
		}
		for (unsigned int i=0;i < mesh->mNumFaces;i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0;j <face.mNumIndices;j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		//process material
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		//diffuse map
		std::vector<MeshModel::Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<MeshModel::Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		std::vector<MeshModel::Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		

		return MeshModel{ vertices,indices,textures };
	}

	unsigned int Model::TextureFromFile(const char* path, const std::string& directory, bool gamma)
	{
		std::string filename = std::string(path);
		filename = directory + "/" + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.data(), &width, &height, &nrComponents, 0);

		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}

	std::vector<MeshModel::Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string_view typeName)
	{
		std::vector<MeshModel::Texture> textures;

		for (unsigned int i = 0; i < mat->GetTextureCount(type);i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			for (unsigned int j = 0;j < textures_load.size();j++)
			{
				if (std::strcmp(textures_load[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(textures_load[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{
				MeshModel::Texture texture;
				texture.id = TextureFromFile(str.C_Str(), this->_directory,0);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_load.push_back(texture);
			}
			return textures;
		}
	}
}
