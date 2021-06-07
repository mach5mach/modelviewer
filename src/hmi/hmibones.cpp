#include <hmi/hmibones.h>

#include <spdlog/spdlog.h>

hmi::hmitibia::hmitibia(json config) : hmi::hmibone(config)
{
	spdlog::get("file")->trace("hmitibia constructor");
	spdlog::get("console")->trace("hmitibia constructor");
	
	spdlog::get("file")->trace("hmitibia config {}", config.dump());
	spdlog::get("console")->trace("hmitibia config {}", config.dump());
}

hmi::hmifemur::hmifemur(json config) : hmi::hmibone(config)
{
	spdlog::get("file")->trace("hmifemur constructor");
	spdlog::get("console")->trace("hmifemur constructor");
	
	spdlog::get("file")->trace("hmifemur config {}", config.dump());
	spdlog::get("console")->trace("hmifemur config {}", config.dump());
}
