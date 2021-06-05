#include <hmi/hmigraphicsobject.h>

#include <learnopengl/shader_m.h>

#include <glm/glm.hpp>

hmi::hmigraphicsobject::hmigraphicsobject() : hmi::hmiobject()
{

}

hmi::hmigraphicsobject::hmigraphicsobject(json config) : hmi::hmiobject(config)
{
	mesh = nullptr;
	
}

void hmi::hmigraphicsobject::init()
{
	if(this->config.contains("modelID") && this->config.contains("meshname"))
	{
		//this->mesh = &(this->scene->model->meshes[this->scene->model->GetMeshIndexByName(this->config["meshname"])]);
	}
}

void hmi::hmigraphicsobject::render(Shader &shader, glm::mat4 modelMatrix)
{
	this->mesh->Draw(shader, modelMatrix);
}

hmi::hmigraphicsobject::~hmigraphicsobject()
{
	if(this->mesh != nullptr)
	{
		delete this->mesh;
	}
	this->mesh = nullptr;
}
