#include <hmi/hmibone.h>

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
