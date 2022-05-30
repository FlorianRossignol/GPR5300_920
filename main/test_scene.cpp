#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "engine.h"
#include "file_utility.h"
#include "scene.h"
#include "Pipeline.h"
#include "Create_texture.h"
#include "Cube.h"


namespace gpr5300
{
	class Test final : public Scene
	{
	public:

		void Begin() override;
		void Update(float dt) override;
		void Deleted() override;

	private:
		gpr5300::Cube cube_;
		gpr5300::Pipeline pipeline_;
		gpr5300::Texture texture_;
		gpr5300::Camera camera_;
		float tt_ = 0.0f;
	};

	void Test::Begin()
	{
		glEnable(GL_DEPTH_TEST);
		camera_.SetCamera(tt_);
		cube_.init();
		texture_.createTexture("data/images/florian.jpeg");
		pipeline_.Load("data/shaders/hello_triangle/triangle.vert", "data/shaders/hello_triangle/triangle.frag");
		pipeline_.SetInt("ourTexture",0);
		texture_.Bind();
	}

	void Test::Update(float dt)
	{
		//setup frame and deltatime
		tt_ += dt;
		/*float lastFrame_ = 0.0f;
		float current_frame = dt += lastFrame_;
		dt = current_frame - lastFrame_;
		lastFrame_ = current_frame;*/

		//camera init and input
		camera_.ProcessInput(dt);
		//matrix generated
		auto model = glm::rotate(camera_.model_, tt_ * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		auto view = glm::translate(camera_.view_, glm::vec3(0.0f, 0.0f, -3.0f));
		auto projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

		pipeline_.SetMatrix(model, "model");
		pipeline_.SetMatrix(view, "view");
		pipeline_.SetMatrix(projection, "projection");

		cube_.Draw();
	}

	void Test::Deleted()
	{
		pipeline_.Delete();
		texture_.deletedTexture();
		cube_.Deleted();
	}
}

int main(int argc, char** argv)
{
	gpr5300::Test test;
	gpr5300::Engine engine(&test);
	engine.Run();
	return EXIT_SUCCESS;
}