#include <hmi/hmimuscles.h>

#include <spdlog/spdlog.h>

hmi::hmihamstring::hmihamstring(json config) : hmi::hmimuscle(config)
{
	spdlog::get("file")->trace("hmihamstring constructor");
	spdlog::get("console")->trace("hmihamstring constructor");
	
	spdlog::get("file")->trace("hmihamstring config {}", config.dump());
	spdlog::get("console")->trace("hmihamstring config {}", config.dump());
}

hmi::hmiquad::hmiquad(json config) : hmi::hmimuscle(config)
{
	spdlog::get("file")->trace("hmiquad constructor");
	spdlog::get("console")->trace("hmiquad constructor");
	
	spdlog::get("file")->trace("hmiquad config {}", config.dump());
	spdlog::get("console")->trace("hmiquad config {}", config.dump());
}
