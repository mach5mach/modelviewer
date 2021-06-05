#ifndef HMIMUSCLE_H
#define HMIMUSCLE_H

#include <hmi/hmianatomyobject.h>

namespace hmi
{
	class hmimuscle : public hmianatomyobject {
		public:
			float contractionState = 0.5;
			float minContraction = 0.0;
			float maxContraction = 1.0;
		
			hmimuscle();
		
			hmimuscle(json config);
			
			void contract(float contractAmount);
			
			void relax(float contractAmount);
		
		protected:
		
		private:
	};
}





#endif
