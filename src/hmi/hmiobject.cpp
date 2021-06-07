#include <hmi/hmiobject.h>

#include <spdlog/spdlog.h>

hmi::hmiobject::hmiobject()
{
}

hmi::hmiobject::hmiobject(json config)
{
	spdlog::get("file")->trace("hmiobject constructor");
	spdlog::get("console")->trace("hmiobject constructor");
	
	spdlog::get("file")->trace("hmiobject config {}", config.dump());
	spdlog::get("console")->trace("hmiobject config {}", config.dump());

	this->config = config;
}

hmi::hmiobject::~hmiobject()
{
}	
