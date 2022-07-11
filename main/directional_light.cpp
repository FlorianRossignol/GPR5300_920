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
		gpr5300::MeshModel cubemesh_;
		gpr5300::Shader pipelinecube_;
		gpr5300::Shader lightPipeline_;
		gpr5300::Shader CameraPipeline_;
		gpr5300::Texture texturecube_;
		gpr5300::Texture specularMapTexture_;
		gpr5300::Camera camera_;
		gpr5300::Light light_;
		float tt_ = 0.0f;
		std::string_view cubeVert = "data/shaders/hello_triangle/directionallight.vert";
		std::string_view cubeFrag = "data/shaders/hello_triangle/directionallight.frag";
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
		texturecube_.createTexture("data/images/florian.jpeg");
		specularMapTexture_.createTexture("data/images/container2_specular.png");
		lightPipeline_.Load(lightVert, lightFrag);
		pipelinecube_.Load(cubeVert, cubeFrag);

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
		auto projection = glm::perspective(glm::radians(camera_.zoom_), float(camera_.SCR_WIDTH) / float(camera_.SCR_HEIGHT), 0.1f, 100.0f);
		CheckError(__FILE__, __LINE__);

		//set Matrix cube
		//set program
		pipelinecube_.Use();
		//set matrix model view projection
		pipelinecube_.SetMatrix(view, "view");
		pipelinecube_.SetMatrix(projection, "projection");
		//set uniform for light
		pipelinecube_.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
		pipelinecube_.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
		pipelinecube_.SetVec3("viewPos", camera_.cameraPos);
		//set material spec
		pipelinecube_.SetFloat("material.shininess", 32.0f);
		//setvector3 and int for cube texture pipeline
		pipelinecube_.SetInt("material.diffuse", 0);
		//bind texture
		texturecube_.Bind();
		//speculartexture
		pipelinecube_.SetInt("material.specular", 1);
		//bind for specular
		specularMapTexture_.BindTextureSpecular();
		//set light pos amb, diff and specular
		pipelinecube_.SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		pipelinecube_.SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		pipelinecube_.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);
		pipelinecube_.SetVec3("light.direction", -0.2f, -1.0f, -0.3f);
		CheckError(__FILE__, __LINE__);

		//draw cube model for directionallight
		for (unsigned int i = 0; i < 10; i++)
		{
			auto model = camera_.model_;
			model = glm::translate(model, light_.lightPos[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			pipelinecube_.SetMatrix(model, "model");
			//draw cube
			cubemesh_.Draw();
		}

		CheckError(__FILE__, __LINE__);


		//set vec3 for lightcube
		//SET MATRIX light
		lightPipeline_.Use();
		lightPipeline_.SetMatrix(view, "view");
		lightPipeline_.SetMatrix(projection, "projection");
		CheckError(__FILE__, __LINE__);
		//setup Model light directional
		auto model = camera_.model_;
		model = glm::translate(model, light_.lightpos_);
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
		texturecube_.deletedTexture();
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