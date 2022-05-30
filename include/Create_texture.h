#pragma once
#include <string_view>


namespace gpr5300
{
	class Texture 
	{
	public:
		Texture();
		void createTexture(std::string_view file_path_texture_image);
		void deletedTexture();
		void Bind();
	private:
		int width_;
		int height_;
		int nrChannels_;
		unsigned int texture_;
	};

}
