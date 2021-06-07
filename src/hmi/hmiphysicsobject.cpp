#include <hmi/hmiphysicsobject.h>

#include <spdlog/spdlog.h>

hmi::hmiphysicsobject::hmiphysicsobject() : hmi::hmiobject()
{
}

hmi::hmiphysicsobject::hmiphysicsobject(json config) : hmi::hmiobject(config)
{
	spdlog::get("file")->trace("hmiphysicsobject constructor");
	spdlog::get("console")->trace("hmiphysicsobject constructor");
	
	spdlog::get("file")->trace("hmiphysicsobject config {}", config.dump());
	spdlog::get("console")->trace("hmiphysicsobject config {}", config.dump());
}

void hmi::hmiphysicsobject::init()
{
	spdlog::get("file")->trace("hmiphysicsobject init");
	spdlog::get("console")->trace("hmiphysicsobject init");
}

hmi::hmiphysicsobject::~hmiphysicsobject()
{

}
