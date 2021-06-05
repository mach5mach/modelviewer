//base physics object

#ifndef HMIPHYSICSOBJECT_H
#define HMIPHYSICSOBJECT_H

#include <hmi/hmiobject.h>

namespace hmi
{
	class hmiphysicsobject : public hmiobject {
		public:		
			hmiphysicsobject();
		
			hmiphysicsobject(json config);
			
			void init();
			
			~hmiphysicsobject();
		protected:
		
		
		private:
		
	};
}

#endif
