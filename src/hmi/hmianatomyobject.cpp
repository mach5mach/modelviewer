#include <hmi/hmianatomyobject.h>

#include <spdlog/spdlog.h>

hmi::hmianatomyobject::hmianatomyobject() : hmi::hmiobject()
{
	this->name = "";
	this->hmigfxobj = nullptr;
	hmiphsxobj = nullptr;
}

hmi::hmianatomyobject::hmianatomyobject(json config) : hmi::hmiobject(config)
{		
	spdlog::get("file")->trace("hmianatomyobject constructor");
	spdlog::get("console")->trace("hmianatomyobject constructor");
	
	spdlog::get("file")->trace("hmianatomyobject config {}", this->config.dump());
	spdlog::get("console")->trace("hmianatomyobject config {}", this->config.dump());

	this->name = "";
	this->hmigfxobj = nullptr;
	this->hmiphsxobj = nullptr;
	
	if(this->config.contains("name"))
	{
		this->name = this->config["name"];
	}
	
	if(this->config.contains("graphics"))
	{
		this->hmigfxobj = new hmigraphicsobject(this->config["graphics"]);
	}
	if(this->config.contains("physics"))
	{
		this->hmiphsxobj = new hmiphysicsobject(this->config["physics"]);
	}
}

void hmi::hmianatomyobject::init() {
	spdlog::get("file")->trace("hmianatomyobject init");
	spdlog::get("console")->trace("hmianatomyobject init");

	hmigfxobj->init();
	
	hmiphsxobj->init();
}

void hmi::hmianatomyobject::render(Shader &shader, glm::mat4 modelMatrix) {
	hmigfxobj->render(shader, modelMatrix);
}

hmi::hmianatomyobject::~hmianatomyobject()
{
}
