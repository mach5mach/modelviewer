#include <hmi/hmimuscle.h>

hmi::hmimuscle::hmimuscle() : hmi::hmianatomyobject()
{
}

hmi::hmimuscle::hmimuscle(json config) : hmi::hmianatomyobject(config)
{

}
			
void hmi::hmimuscle::contract(float contractAmount)
{
	contractionState += contractAmount;
	if(contractionState > maxContraction)
	{
		contractionState = maxContraction;
	}
}

void hmi::hmimuscle::relax(float contractAmount)
{
	contractionState -= contractAmount;
	if(contractionState < minContraction)
	{
		contractionState = minContraction;
	}
}
