#define STB_IMAGE_IMPLEMENTATION
#include <hmi/hmiscene.h>

#include <hmi/hmiwindow.h>
#include <hmi/hmimuscles.h>
#include <hmi/hmibones.h>


#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>


#include <string>
#include <stdio.h>
#include <vector>

using json = nlohmann::json;

hmi::hmiscene::hmiscene()
{
	this->id = -1;
	this->name = "";
	this->clearcolor = glm::vec4(0.0f);
	
	camera = NULL;
	shader = NULL;
	model = NULL;
}

hmi::hmiscene::hmiscene(json config)
{
	spdlog::get("file")->trace("hmiscene constructor");
	spdlog::get("console")->trace("hmiscene constructor");
	
	spdlog::get("file")->trace("hmiscene config {}", config.dump());
	spdlog::get("console")->trace("hmiscene config {}", config.dump());

	this->config = config;

	this->id = config["id"];
	this->name = config["name"];
	this->clearcolor = glm::vec4(config["clearcolor"][0], config["clearcolor"][1], config["clearcolor"][2], config["clearcolor"][3]);
	
	this->vertShaderFileName = config["shaders"]["vert"];
	this->geomShaderFileName = config["shaders"]["geom"];
	this->fragShaderFileName = config["shaders"]["frag"];
	
	this->modelFileName = config["models"][0]["filename"];
	this->modelPosition = glm::vec3((float)config["models"][0]["position"][0], (float)config["models"][0]["position"][1], (float)config["models"][0]["position"][2]);
	this->modelScale = glm::vec3((float)config["models"][0]["scale"][0], (float)config["models"][0]["scale"][1], (float)config["models"][0]["scale"][2]);
	
	
	this->cameraPosition = glm::vec3(config["camera"]["position"][0], config["camera"]["position"][1], config["camera"]["position"][2]);
	this->cameraClipping = glm::vec2((float)config["camera"]["clipping"][0], (float)config["camera"]["clipping"][1]);
	
	camera = NULL;
	shader = NULL;
	model = NULL;
}

void hmi::hmiscene::Init()
{
	spdlog::get("file")->trace("hmiscene init");
	spdlog::get("console")->trace("hmiscene init");
	
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		spdlog::get("file")->error("glewInit failed: {}", glGetString(err));
		spdlog::get("console")->error("glewInit failed: {}", glGetString(err));
	}
	
	glEnable(GL_DEPTH_TEST);
	
	ClearColor(this->clearcolor);
	
	stbi_set_flip_vertically_on_load(true);

	shader = new Shader(vertShaderFileName.c_str(), fragShaderFileName.c_str());

	model = new Model(modelFileName.c_str());
	
	camera = new Camera(cameraPosition);
	
	if(this->config.contains("hamstring")){		
		anatObjs.push_back(hmi::hmihamstring(this->config["hamstring"]));
	}
	if(this->config.contains("quad")){				
		anatObjs.push_back(hmi::hmiquad(this->config["quad"]));
		spdlog::get("console")->trace("quad finished");
	}			
	if(this->config.contains("femur")){
		spdlog::get("console")->trace("femur");
		anatObjs.push_back(hmi::hmifemur(this->config["femur"]));
	}
	if(this->config.contains("tibia")){
		anatObjs.push_back(hmi::hmitibia(this->config["tibia"]));
	}
	
	for(hmianatomyobject anatObj : anatObjs)
	{
		anatObj.hmigfxobj->mesh = &(this->model->meshes[this->model->GetMeshIndexByName(anatObj.hmigfxobj->config["meshname"])]);
		anatObj.init();
	}
}

void hmi::hmiscene::Render(hmi::hmiwindow* window)
{
	// render
	// ------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// don't forget to enable shader before setting uniforms
	shader->use();

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)window->width / (float)window->height, cameraClipping[0], cameraClipping[1]);
	glm::mat4 view = camera->GetViewMatrix();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, modelPosition); // translate it down so it's at the center of the scene
	model = glm::scale(model, modelScale);	// it's a bit too big for our scene, so scale it down
	//this->model->Draw(*shader, model);

	for(hmianatomyobject anatObj : anatObjs)
	{
		anatObj.render(*shader, model);
	}

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window->glfwwindow);
	glfwPollEvents();
}

void hmi::hmiscene::ClearColor(glm::vec4 color)
{
	spdlog::get("file")->trace("hmiscene clearcolor color {} {} {} {}", color[0], color[1], color[2], color[3]);
	spdlog::get("console")->trace("hmiscene clearcolor color {} {} {} {}", color[0], color[1], color[2], color[3]);
	
	glClearColor(color[0], color[1], color[2], color[3]);
}
