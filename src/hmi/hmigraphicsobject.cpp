#include <hmi/hmigraphicsobject.h>

#include <learnopengl/shader_m.h>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

hmi::hmigraphicsobject::hmigraphicsobject() : hmi::hmiobject()
{
}

hmi::hmigraphicsobject::hmigraphicsobject(json config) : hmi::hmiobject(config)
{
	spdlog::get("file")->trace("hmigraphicsobject constructor");
	spdlog::get("console")->trace("hmigraphicsobject constructor");
	
	spdlog::get("file")->trace("hmigraphicsobject config {}", config.dump());
	spdlog::get("console")->trace("hmigraphicsobject config {}", config.dump());

	mesh = nullptr;
	
}

void hmi::hmigraphicsobject::init()
{
	spdlog::get("file")->trace("hmigraphicsobject init");
	spdlog::get("console")->trace("hmigraphicsobject init");
	
	if(this->config.contains("modelID") && this->config.contains("meshname"))
	{
		//this->mesh = &(this->scene->model->meshes[this->scene->model->GetMeshIndexByName(this->config["meshname"])]);
	}
}

void hmi::hmigraphicsobject::render(Shader &shader, glm::mat4 modelMatrix)
{
	if(this->mesh != nullptr)
	{
		this->mesh->Draw(shader, modelMatrix);
	}
}

hmi::hmigraphicsobject::~hmigraphicsobject()
{
}
