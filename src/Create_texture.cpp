#include "Create_texture.h"

#include <iostream>


#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

namespace gpr5300
{
	Texture::Texture()
	{
	}

	void Texture::createTexture(std::string_view file_path_texture_image)
	{
		unsigned char* data = stbi_load(file_path_texture_image.data(), &width_, &height_, &nrChannels_, 0);
		if (!data)
		{
			std::cerr << "cant open the file image\n";
		}

		////texture to gpu and mipmap
		switch (nrChannels_)
		{
		case 3:
			glGenTextures(1, &texture_);
			glBindTexture(GL_TEXTURE_2D, texture_);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case 4:
			glGenTextures(1, &texture_);
			glBindTexture(GL_TEXTURE_2D, texture_);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
			default:
				break;
		}

		//texture wrapping and filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void Texture::deletedTexture()
	{
		glDeleteTextures(1, &texture_);
	}

	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_);
	}

	void Texture::BindTextureSpecular()
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_);
	}
}
