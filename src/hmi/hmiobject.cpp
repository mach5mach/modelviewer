#include <hmi/hmiobject.h>

hmi::hmiobject::hmiobject()
{

}

hmi::hmiobject::hmiobject(json config)
{
	this->config = config;
}

hmi::hmiobject::~hmiobject()
{
}	
