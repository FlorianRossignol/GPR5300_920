#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "engine.h"
#include "file_utility.h"
#include "scene.h"
#include "Shader.h"
#include "Create_texture.h"
#include "MeshModel.h"
#include "Light.h"


namespace gpr5300
{
	class Test final : public Scene
	{
	public:

		void Begin() override;
		void Update(float dt) override;
		void Deleted() override;

	private:
		gpr5300::MeshModel mesh_;
		gpr5300::Shader pipeline_;
		gpr5300::Texture texture_;
		gpr5300::Camera camera_;
		gpr5300::Light light_;
		float tt_ = 0.0f;
	};

	void Test::Begin()
	{
		glEnable(GL_DEPTH_TEST);
		camera_.SetCamera(tt_);
		mesh_.init();
		texture_.createTexture("data/images/florian.jpeg");
		pipeline_.Load("data/shaders/hello_triangle/triangle.vert", "data/shaders/hello_triangle/triangle.frag");
		pipeline_.SetInt("ourTexture",0);
	
		texture_.Bind();
	}

	void Test::Update(float dt)
	{
		//setup frame and deltatime
		tt_ += dt;
		
		//camera init and input
		camera_.ProcessInput(dt);

		//matrix generated
		auto model = glm::rotate(camera_.model_, tt_ * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		auto view = glm::translate(camera_.view_, glm::vec3(0.0f, 0.0f, -3.0f));
		auto projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

		//SET MATRIX1
		pipeline_.SetMatrix(model, "model");
		pipeline_.SetMatrix(view, "view");
		pipeline_.SetMatrix(projection, "projection");
		
		mesh_.Draw();
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