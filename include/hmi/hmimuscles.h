#ifndef HMIMUSCLES_H
#define HMIMUSCLES_H

#include <hmi/hmimuscle.h>

namespace hmi
{	

	class hmihamstring : public hmimuscle {
		public:
			hmihamstring(json config);
		protected:
		
		private:
	};
	
	class hmiquad : public hmimuscle {
		public:
			hmiquad(json config);
		
		protected:
		
		private:
	};
}





#endif
