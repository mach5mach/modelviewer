#ifndef HMIBONE_H
#define HMIBONE_H

#include <hmi/hmianatomyobject.h>

namespace hmi
{
	class hmibone : public hmianatomyobject {
		public:
			hmibone();
			
			hmibone(json config);
		
			virtual void rotate(float rotationDeg, glm::vec3 rotationAxis);
		protected:
		
		private:
	};
}





#endif
