//base anatomy object

#ifndef HMIANATOMYOBJECT_H
#define HMIANATOMYOBJECT_H

#include <hmi/hmigraphicsobject.h>
#include <hmi/hmiphysicsobject.h>

namespace hmi
{
	class hmianatomyobject : public hmiobject {
		public:
			hmigraphicsobject* hmigfxobj;
			hmiphysicsobject* hmiphsxobj;		
		
			hmianatomyobject();
			hmianatomyobject(json config);
			
			void init();
			
			void render(Shader &shader, glm::mat4 modelMatrix);
		
			~hmianatomyobject();
		
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
