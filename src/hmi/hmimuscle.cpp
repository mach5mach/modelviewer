#include <hmi/hmimuscle.h>

#include <spdlog/spdlog.h>

hmi::hmimuscle::hmimuscle() : hmi::hmianatomyobject()
{
}

hmi::hmimuscle::hmimuscle(json config) : hmi::hmianatomyobject(config)
{
	spdlog::get("file")->trace("hmimuscle constructor");
	spdlog::get("console")->trace("hmimuscle constructor");
	
	spdlog::get("file")->trace("hmimuscle config {}", config.dump());
	spdlog::get("console")->trace("hmimuscle config {}", config.dump());
}
			
void hmi::hmimuscle::contract(float contractAmount)
{
	spdlog::get("file")->trace("hmimuscle contract");
	spdlog::get("console")->trace("hmimuscle contract");
	
	spdlog::get("file")->trace("contractAmount {}", contractAmount);
	spdlog::get("console")->trace("contractAmount {}", contractAmount);
	
	spdlog::get("file")->trace("contractionState before {}", contractionState);
	spdlog::get("console")->trace("contractionState before {}", contractionState);
	
	spdlog::get("file")->trace("maxContraction {}", maxContraction);
	spdlog::get("console")->trace("maxContraction {}", maxContraction);
	
	contractionState += contractAmount;
	if(contractionState > maxContraction)
	{
		contractionState = maxContraction;
	}
	
	spdlog::get("file")->trace("contractionState after {}", contractionState);
	spdlog::get("console")->trace("contractionState after {}", contractionState);
}

void hmi::hmimuscle::relax(float contractAmount)
{
	spdlog::get("file")->trace("hmimuscle relax");
	spdlog::get("console")->trace("hmimuscle relax");
	
	spdlog::get("file")->trace("contractAmount {}", contractAmount);
	spdlog::get("console")->trace("contractAmount {}", contractAmount);
	
	spdlog::get("file")->trace("contractionState before {}", contractionState);
	spdlog::get("console")->trace("contractionState before {}", contractionState);
	
	spdlog::get("file")->trace("maxContraction {}", maxContraction);
	spdlog::get("console")->trace("maxContraction {}", maxContraction);

	contractionState -= contractAmount;
	if(contractionState < minContraction)
	{
		contractionState = minContraction;
	}
	
	spdlog::get("file")->trace("contractionState after {}", contractionState);
	spdlog::get("console")->trace("contractionState after {}", contractionState);
}
