
#include <glm/ext/matrix_clip_space.hpp>
#include "engine.h"
#include "file_utility.h"
#include "scene.h"
#include "Shader.h"
#include "Create_texture.h"
#include "MeshModel.h"
#include "Light.h"
#include "error.h"
#include "Camera.h"
#include "Model.h"
#include "cubemap.h"
#include "stb_image.h"
#include "Framebuffer.h"

namespace gpr5300
{
	class Test final : public Scene
	{
	public:

		void Begin() override;
		void Update(float dt) override;
		void Deleted() override;
		void OnEvent(const SDL_Event& event) override;

	private:
		gpr5300::MeshBasic cubemesh_;
		gpr5300::Shader skybox_;
		gpr5300::Shader shaderModel_;
		gpr5300::Texture texturecube_;
		gpr5300::Texture specularMapTexture_;
		gpr5300::Camera camera_;
		gpr5300::Light light_;
		gpr5300::CubeMap cubeMap_;
		Model modeltt_;
		gpr5300::Framebuffer frameBuffer_;
		float tt_ = 0.0f;
		std::string_view modelVert = "data/shaders/hello_triangle/instancing.vert";
		std::string_view cubeFrag = "data/shaders/hello_triangle/instancing.frag";
		
		std::string_view skyboxVert = "data/shaders/hello_triangle/skybox.vert";
		std::string_view skyboxFrag = "data/shaders/hello_triangle/skybox.frag";

		std::string_view modelPath_ = "data/obj/backpack/backpack.obj";

	};

	void Test::Begin()
	{
		//enable stencil
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		//enable depth test
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		//camera and mesh init, setup vao light
		camera_.SetCamera(tt_);

		//error check
		CheckError(__FILE__, __LINE__);
		//load basicobject
		shaderModel_.Load(modelVert, cubeFrag);
		//loadmodel
		modeltt_.Load(modelPath_.data(), true);

		//load skybox
		skybox_.Load(skyboxVert, skyboxFrag);

		//load cubemap
		cubeMap_.loadCubemap(cubeMap_.cubeMapfaces);
		cubeMap_.BindSky();

		//init instancing model matrix
		shaderModel_.Use();
		 auto modelMatrices = new glm::mat4[modeltt_.amout_];
		for (unsigned int i = 0; i < modeltt_.amout_; i++)
		{
			constexpr float offset = 3.0f;
			auto model = glm::mat4(1.0f);

			model = translate(model, glm::vec3(offset * i * 2, 0.0, 0.0));

			model = scale(model, glm::vec3(1, 1, 1));

			modelMatrices[i] = model;
		}

		//init buffer
		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, modeltt_.amout_ * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
		for (unsigned int i = 0; i < modeltt_.meshes_.size(); i++)
		{
			unsigned int VAO = modeltt_.meshes_[i].vao_;
			glBindVertexArray(VAO);
			// vertex attributes
			std::size_t vec4Size = sizeof(glm::vec4);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
			glEnableVertexAttribArray(7);
			glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);
			glVertexAttribDivisor(6, 1);
			glVertexAttribDivisor(7, 1);

			glBindVertexArray(0);
		}
		//error check
		CheckError(__FILE__, __LINE__);
	}

	void Test::Update(float dt)
	{
		//setup frame and deltatime
		tt_ += dt;
		CheckError(__FILE__, __LINE__);

		//set input
		camera_.ProcessInput(dt);
		//Matrix cube
		//view projection matrix
		auto model = camera_.model_;
		auto view = camera_.GetViewMatrix();
		auto projection = glm::perspective(glm::radians(camera_.zoom_), float(camera_.SCR_WIDTH) / float(camera_.SCR_HEIGHT), 0.1f, 100.0f);
		CheckError(__FILE__, __LINE__);
		//set program
		shaderModel_.Use();
		//set Matrix cube
		shaderModel_.SetMatrix(view, "view");
		shaderModel_.SetMatrix(projection, "projection");

		//rendermodelS
		shaderModel_.SetMatrix(model, "model");
		CheckError(__FILE__, __LINE__);
		//drawcube
		modeltt_.MultipleDraw(shaderModel_);
		CheckError(__FILE__, __LINE__);


		//drawSkybox
		glDepthFunc(GL_LEQUAL);
		skybox_.Use();
		skybox_.SetInt("skybox", 0);
		view = glm::mat4(glm::mat3(camera_.GetViewMatrix()));
		skybox_.SetMatrix(view, "view");
		skybox_.SetMatrix(projection, "projection");
		//skyboxcube
		glBindVertexArray(cubeMap_.skyvao);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap_.cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthFunc(GL_LESS);
	}

	void Test::Deleted()
	{
		shaderModel_.Delete();
		texturecube_.deletedTexture();
		cubemesh_.Deleted();
		light_.Deleted();
	}

	void Test::OnEvent(const SDL_Event& event)
	{
		camera_.OnEvent(event);
	}
}

int main(int argc, char** argv)
{
	gpr5300::Test test;
	gpr5300::Engine engine(&test);
	engine.Run();
	return EXIT_SUCCESS;
}