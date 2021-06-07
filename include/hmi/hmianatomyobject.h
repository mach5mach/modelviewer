//base anatomy object

#ifndef HMIANATOMYOBJECT_H
#define HMIANATOMYOBJECT_H

#include <hmi/hmigraphicsobject.h>
#include <hmi/hmiphysicsobject.h>

#include <string>

namespace hmi
{
	class hmianatomyobject : public hmiobject {
		public:
			std::string name;
		
			hmigraphicsobject* hmigfxobj;
			hmiphysicsobject* hmiphsxobj;		
		
			hmianatomyobject();
			hmianatomyobject(json config);
			
			void init();
			
			virtual void render(Shader &shader, glm::mat4 modelMatrix);
		
			virtual ~hmianatomyobject();
		
			/*
			virtual void ProcessKeyboard(int action, float deltaTime);
			virtual void ProcessMouseScroll(int xoffset, int yoffset);
			virtual void ProcessMouseMovement(int xpos, int ypos);
			*/
		protected:
		
		
		private:
		
	};
}

#endif
