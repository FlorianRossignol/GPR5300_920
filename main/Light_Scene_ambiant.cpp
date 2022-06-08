#include <glm/ext/matrix_clip_space.hpp>

#include "engine.h"
#include "file_utility.h"
#include "scene.h"
#include "Pipeline.h"
#include "Create_texture.h"
#include "Mesh.h"
#include "Light.h"
#include "Error_check.h"
#include "imgui.h"


namespace gpr5300
{
	class Test final : public Scene
	{
	public:

		void Begin() override;
		void Update(float dt) override;
		void Deleted() override;

	private:
		gpr5300::Cube mesh_;
		gpr5300::Pipeline pipeline_;
		gpr5300::Texture texture_;
		gpr5300::Camera camera_;
		gpr5300::Light light_;
		gpr5300::Error error_;
		float tt_ = 0.0f;
	};

	void Test::Begin()
	{
		//camera and mesh init, setup vao light
		glEnable(GL_DEPTH_TEST);
		camera_.SetCamera(tt_);
		mesh_.init();
		light_.SetVao();

		//clear
		/*glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);*/

		//load and compile texture and shader
		texture_.createTexture("data/images/florian.jpeg");
		pipeline_.Load("data/shaders/hello_triangle/ambient.vert", "data/shaders/hello_triangle/ambient.frag");
		pipeline_.Load("data/shaders/hello_triangle/triangle.vert", "data/shaders/hello_triangle/triangle.frag");

		//setvector3
		pipeline_.SetInt("ourTexture", 0);
		pipeline_.SetVec3("objectColor", { 1.0f, 0.5f, 0.31f });
		pipeline_.SetVec3("lightColor", { 1.0f,1.0f,1.0f });

		//error check
		error_.glCheckError("LightScene_ambiant", 81);
		
		//bind texture
		texture_.Bind();
	}

	void Test::Update(float dt)
	{
		//setup frame and deltatime
		tt_ += dt;

		//camera init and input
		camera_.ProcessInput(dt);

		//imgui
		/*int display_w, display_h;
		ImGui::NewFrame();
		ImGui::Begin("Show,fps");
		ImGui::Text("lol");
		ImGui::Text("FPS %.1f FPS", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::End();
		ImGui::Render();
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);*/

		//Matrix cube
		auto model = glm::rotate(camera_.model_, tt_ * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		auto view = glm::translate(camera_.view_, glm::vec3(0.0f, 0.0f, -3.0f));
		auto projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

		//set Matrix cube
		pipeline_.SetMatrix(model, "model");
		pipeline_.SetMatrix(view, "view");
		pipeline_.SetMatrix(projection, "projection");

		//draw cube
		mesh_.Draw();

		//MATRIX LIGHT
		auto modelLight = glm::mat4(1.0f);
		auto viewLight = glm::translate(modelLight, light_.lightPos);
		auto projection2 = glm::scale(modelLight, glm::vec3(0.2f));

		//SET MATRIX2
		pipeline_.SetMatrix(modelLight, "model");
		pipeline_.SetMatrix(viewLight, "view");
		pipeline_.SetMatrix(projection2, "projection");


		//setup Model cam
		auto modell_ = glm::mat4(1.0f);
		modell_ = glm::translate(camera_.model_, light_.lightPos);
		modell_ = glm::scale(camera_.model_, glm::vec3(0.2f));
		pipeline_.SetMatrix(modell_, "model");

		//draw lightcube
		error_.glCheckError("UpdateSceneambiant", 115);
		light_.Draw();
	}

	void Test::Deleted()
	{
		pipeline_.Delete();
		texture_.deletedTexture();
		mesh_.Deleted();
	}
}

int main(int argc, char** argv)
{
	gpr5300::Test test;
	gpr5300::Engine engine(&test);
	engine.Run();
	return EXIT_SUCCESS;
}