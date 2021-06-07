#include <hmi/hmibone.h>

#include <glm/glm.hpp>

#include <spdlog/spdlog.h>

hmi::hmibone::hmibone() : hmi::hmianatomyobject()
{
}

hmi::hmibone::hmibone(json config) : hmi::hmianatomyobject(config)
{
	spdlog::get("file")->trace("hmibone constructor");
	spdlog::get("console")->trace("hmibone constructor");
	
	spdlog::get("file")->trace("hmibone config {}", config.dump());
	spdlog::get("console")->trace("hmibone config {}", config.dump());
}

void hmi::hmibone::rotate(float rotationDeg, glm::vec3 rotationAxis)
{
	spdlog::get("file")->trace("rotate {} about {} {} {}", rotationDeg, rotationAxis[0], rotationAxis[1], rotationAxis[2]);
	spdlog::get("console")->trace("rotate {} about {} {} {}", rotationDeg, rotationAxis[0], rotationAxis[1], rotationAxis[2]);

	this->hmigfxobj->mesh->rotationDeg += rotationDeg;
	
	this->hmigfxobj->mesh->rotation = rotationAxis;
}
