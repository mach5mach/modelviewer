#include <hmi/hmianatomyobject.h>

hmi::hmianatomyobject::hmianatomyobject() : hmi::hmiobject()
{
	hmigfxobj = nullptr;
	hmiphsxobj = nullptr;
}

hmi::hmianatomyobject::hmianatomyobject(json config) : hmi::hmiobject(config)
{		
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
	hmigfxobj->init();
	
	hmiphsxobj->init();
}

void hmi::hmianatomyobject::render(Shader &shader, glm::mat4 modelMatrix) {
	hmigfxobj->render(shader, modelMatrix);
}

hmi::hmianatomyobject::~hmianatomyobject()
{
	if(hmigfxobj != nullptr)
	{
		delete hmigfxobj;
	}
	hmigfxobj = nullptr;
	
	if(hmiphsxobj != nullptr)
	{
		delete hmiphsxobj;
	}
	hmiphsxobj = nullptr;
}
