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

hmi::hmiscene::hmiscene(json scene)
{
	this->id = scene["id"];
	this->name = scene["name"];
	this->clearcolor = glm::vec4(scene["clearcolor"][0], scene["clearcolor"][1], scene["clearcolor"][2], scene["clearcolor"][3]);
	
	this->vertShaderFileName = scene["shaders"]["vert"];
	this->geomShaderFileName = scene["shaders"]["geom"];
	this->fragShaderFileName = scene["shaders"]["frag"];
	
	this->modelFileName = scene["models"][0]["filename"];
	this->modelPosition = glm::vec3((float)scene["models"][0]["position"][0], (float)scene["models"][0]["position"][1], (float)scene["models"][0]["position"][2]);
	this->modelScale = glm::vec3((float)scene["models"][0]["scale"][0], (float)scene["models"][0]["scale"][1], (float)scene["models"][0]["scale"][2]);
	
	
	this->cameraPosition = glm::vec3(scene["camera"]["position"][0], scene["camera"]["position"][1], scene["camera"]["position"][2]);
	this->cameraClipping = glm::vec2((float)scene["camera"]["clipping"][0], (float)scene["camera"]["clipping"][1]);
	
	camera = NULL;
	shader = NULL;
	model = NULL;
	
	if(scene.contains("hamstring")){
		hmi::hmihamstring hs(scene["hamstring"]);
		anatObjs.push_back(hs);
	}
	if(scene.contains("quad")){				
		anatObjs.push_back(hmi::hmiquad(scene["quad"]));
	}			
	if(scene.contains("femur")){
		anatObjs.push_back(hmi::hmifemur(scene["femur"]));
	}
	if(scene.contains("tibia")){
		anatObjs.push_back(hmi::hmitibia(scene["tibia"]));
	}
}

void hmi::hmiscene::Init()
{
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
	
	for(hmianatomyobject anatObj : anatObjs)
	{
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
	glClearColor(color[0], color[1], color[2], color[3]);
}
