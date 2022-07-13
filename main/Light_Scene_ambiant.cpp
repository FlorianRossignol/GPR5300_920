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
		gpr5300::MeshBasic mesh_;
		gpr5300::Shader pipeline_;
		gpr5300::Shader lightPipeline_;
		gpr5300::Shader CameraPipeline_;
		gpr5300::Texture texture_;
		gpr5300::Camera camera_;
		gpr5300::Light light_;
		float tt_ = 0.0f;
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

		
		light_.SetVao();

		//error check
		CheckError(__FILE__, __LINE__);

		//load and compile texture and shader
		texture_.createTexture("data/images/florian.jpeg");
		lightPipeline_.Load("data/shaders/hello_triangle/light2.vert", "data/shaders/hello_triangle/light2.frag");
		pipeline_.Load("data/shaders/hello_triangle/ambiant.vert", "data/shaders/hello_triangle/ambiant.frag");
		CameraPipeline_.Load("data/shaders/hello_triangle/camera.vert","data/shaders/hello_triangle/camera.frag");


		//error check
		CheckError(__FILE__, __LINE__);

		//setvector3 and int for cube texture pipeline
		pipeline_.Use();
		pipeline_.SetInt("ourTexture", 0);
		pipeline_.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
		pipeline_.SetVec3("ambient", 0.3f, 0.3f, 0.3f);

		//set vec3 for lightcube
		lightPipeline_.Use();
		lightPipeline_.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
		

		//error check
		CheckError(__FILE__, __LINE__);

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

		//camera set pipeline
		glm::mat4 cameraView_ = camera_.GetViewMatrix();
		CameraPipeline_.Use();
		CameraPipeline_.SetMatrix(cameraView_, "view");
		CheckError(__FILE__, __LINE__);

		//Matrix cube
		auto model = glm::rotate(camera_.model_, tt_ * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		auto view = glm::translate(camera_.view_, glm::vec3(0.0f, 0.0f, -3.0f));
		auto projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
		CheckError(__FILE__, __LINE__);

		//set Matrix cube
		//set program
		pipeline_.Use();
		pipeline_.SetMatrix(model, "model");
		pipeline_.SetMatrix(cameraView_, "view");
		pipeline_.SetMatrix(projection, "projection");
		CheckError(__FILE__, __LINE__);

		//draw cube
		mesh_.Draw();
		CheckError(__FILE__, __LINE__);

		//MATRIX LIGHT
		/*auto modelLight = glm::mat4(1.0f);
		auto viewLight = camera_.GetViewMatrix();
		auto projection2 = glm::perspective(glm::radians(camera_.zoom_), (float)camera_.SCR_WIDTH / (float)camera_.SCR_HEIGHT, 0.1f, 100.0f);
		CheckError(__FILE__, __LINE__);*/

		//SET MATRIX light
		lightPipeline_.Use();
		lightPipeline_.SetMatrix(model, "model");
		lightPipeline_.SetMatrix(view, "view");
		lightPipeline_.SetMatrix(projection, "projection");
		CheckError(__FILE__, __LINE__);

		//setup Model light
		model = glm::mat4(1.0f);
		model = glm::scale(camera_.model_, glm::vec3(0.2f));
		lightPipeline_.SetMatrix(model, "model");
		CheckError(__FILE__, __LINE__);

		//draw lightcube
		light_.Draw();

		//error check
		CheckError(__FILE__, __LINE__);
	}

	void Test::Deleted()
	{
		pipeline_.Delete();
		texture_.deletedTexture();
		light_.Deleted();
		CameraPipeline_.Delete();
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