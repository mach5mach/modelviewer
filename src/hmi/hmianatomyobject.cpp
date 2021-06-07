#include <hmi/hmianatomyobject.h>

#include <spdlog/spdlog.h>

hmi::hmianatomyobject::hmianatomyobject() : hmi::hmiobject()
{
	hmigfxobj = nullptr;
	hmiphsxobj = nullptr;
}

hmi::hmianatomyobject::hmianatomyobject(json config) : hmi::hmiobject(config)
{		
	spdlog::get("file")->trace("hmianatomyobject constructor");
	spdlog::get("console")->trace("hmianatomyobject constructor");
	
	spdlog::get("file")->trace("hmianatomyobject config {}", config.dump());
	spdlog::get("console")->trace("hmianatomyobject config {}", config.dump());

	hmigfxobj = nullptr;
	hmiphsxobj = nullptr;
	
	if(config.contains("graphics"))
	{
		hmigfxobj = new hmigraphicsobject(this->config["graphics"]);
	}
	if(config.contains("physics"))
	{
		hmiphsxobj = new hmiphysicsobject(this->config["physics"]);
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
