//base object for all hmi classes

#ifndef HMIOBJECT_H
#define HMIOBJECT_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace hmi
{
	class hmiobject {
		public:
			json config;
		
			hmiobject();
		
			hmiobject(json config);
			
			virtual ~hmiobject();		
		protected:
		
		
		private:
		
	};
}

#endif
