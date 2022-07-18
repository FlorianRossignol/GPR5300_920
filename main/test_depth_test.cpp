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
		gpr5300::Shader pipelinecube_;
		gpr5300::Shader singleColor_;
		gpr5300::Shader CameraPipeline_;
		gpr5300::Texture texturecube_;
		gpr5300::Texture specularMapTexture_;
		gpr5300::Camera camera_;
		gpr5300::Light light_;
		Model modeltt_;
		float tt_ = 0.0f;
		std::string_view cubeVert = "data/shaders/hello_triangle/depthtest.vert";
		std::string_view cubeFrag = "data/shaders/hello_triangle/depthtest.frag";
		std::string_view lightVert = "data/shaders/hello_triangle/light.vert";
		std::string_view lightFrag = "data/shaders/hello_triangle/light.frag";
		std::string_view modelPath_ = "data/obj/backpack/backpack.obj";

	};

	void Test::Begin()
	{
		//enable depth test
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		//camera and mesh init, setup vao light
		camera_.SetCamera(tt_);

		//error check
		CheckError(__FILE__, __LINE__);

		pipelinecube_.Load(cubeVert, cubeFrag);

		modeltt_.Load(modelPath_.data(), true);
		//error check
		CheckError(__FILE__, __LINE__);
	}

	void Test::Update(float dt)
	{
		//setup frame and deltatime
		tt_ += dt;
		CheckError(__FILE__, __LINE__);
		//set input
		/*camera_.ProcessInput(dt);*/
		camera_.ProcessInput(dt);

		//set program
		pipelinecube_.Use();
		//Matrix cube
		//view projection matrix
		auto view = camera_.GetViewMatrix();
		auto projection = glm::perspective(glm::radians(camera_.zoom_), float(camera_.SCR_WIDTH) / float(camera_.SCR_HEIGHT), 0.1f, 100.0f);
		CheckError(__FILE__, __LINE__);


		//set Matrix cube
		pipelinecube_.SetMatrix(view, "view");
		pipelinecube_.SetMatrix(projection, "projection");

		//rendermodel
		auto modelmatrix = glm::mat4(1.0f);
		modelmatrix = glm::translate(modelmatrix, glm::vec3(0.0f, 0.0f, 0.0f));
		modelmatrix = glm::scale(modelmatrix, glm::vec3(1.0f, 1.0f, 1.0f));
		pipelinecube_.SetMatrix(modelmatrix, "model");
		CheckError(__FILE__, __LINE__);
		//drawcube
		modeltt_.Draw(pipelinecube_);
		CheckError(__FILE__, __LINE__);
	}

	void Test::Deleted()
	{
		pipelinecube_.Delete();
		texturecube_.deletedTexture();
		cubemesh_.Deleted();
		light_.Deleted();
		singleColor_.Delete();
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