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
		gpr5300::Shader lightPipeline_;
		gpr5300::Shader CameraPipeline_;
		gpr5300::Texture texture_;
		gpr5300::Camera camera_;
		gpr5300::Light light_;
		float tt_ = 0.0f;
		glm::vec3 lightPos_ = glm::vec3(0.0f, 0.0f, 2.0f);
		std::string_view cubeVert = "data/shaders/hello_triangle/diffuse.vert";
		std::string_view cubeFrag = "data/shaders/hello_triangle/diffuse.frag";
		std::string_view lightVert = "data/shaders/hello_triangle/light.vert";
		std::string_view lightFrag = "data/shaders/hello_triangle/light.frag";
	};

	void Test::Begin()
	{
		//enable depth test
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);

		//camera and mesh init, setup vao light
		camera_.SetCamera(tt_);

		cubemesh_.initDiffuse();
		light_.SetVao();

		//error check
		CheckError(__FILE__, __LINE__);

		//load and compile texture and shader
		texture_.createTexture("data/images/florian.jpeg");
		lightPipeline_.Load(lightVert, lightFrag);
		pipelinecube_.Load(cubeVert, cubeFrag);


		//error check
		CheckError(__FILE__, __LINE__);

		//setvector3 and int for cube texture pipeline
		pipelinecube_.Use();
		pipelinecube_.SetInt("ourTexture", 0);

		//bind texture
		texture_.Bind();

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

		//Matrix cube
		auto view = camera_.GetViewMatrix();
		auto model = glm::rotate(camera_.model_, tt_ * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		auto projection = glm::perspective(glm::radians(camera_.zoom_), float(camera_.SCR_WIDTH) / float(camera_.SCR_HEIGHT), 0.1f, 100.0f);
		CheckError(__FILE__, __LINE__);

		//set Matrix cube
		//set program
		pipelinecube_.Use();
		pipelinecube_.SetMatrix(model, "model");
		pipelinecube_.SetMatrix(view, "view");
		pipelinecube_.SetMatrix(projection, "projection");
		pipelinecube_.SetVec3("lightPos", lightPos_);
		pipelinecube_.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
		pipelinecube_.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
		pipelinecube_.SetVec3("ambient", 1.0f, 1.0f, 1.0f);
		CheckError(__FILE__, __LINE__);

		//draw cube
		cubemesh_.Draw();
		CheckError(__FILE__, __LINE__);


		//set vec3 for lightcube
		//SET MATRIX light
		lightPipeline_.Use();
		lightPipeline_.SetMatrix(view, "view");
		lightPipeline_.SetMatrix(projection, "projection");
		CheckError(__FILE__, __LINE__);

		//setup Model light
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos_);
		model = glm::scale(model, glm::vec3(0.2f));
		lightPipeline_.SetMatrix(model, "model");
		CheckError(__FILE__, __LINE__);

		//draw lightcube
		light_.Draw();

		//error check
		CheckError(__FILE__, __LINE__);
	}

	void Test::Deleted()
	{
		pipelinecube_.Delete();
		texture_.deletedTexture();
		cubemesh_.Deleted();
		light_.Deleted();
		lightPipeline_.Delete();
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