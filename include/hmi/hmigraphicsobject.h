//base graphics object

#ifndef HMIGRAPHICSOBJECT_H
#define HMIGRAPHICSOBJECT_H

#include <hmi/hmiobject.h>

#include <learnopengl/mesh.h>

namespace hmi
{
	class hmigraphicsobject : public hmiobject {
		public:
			Mesh* mesh;
				
			hmigraphicsobject();
				
			hmigraphicsobject(json config);
			
			virtual void init();
			
			virtual void render(Shader &shader, glm::mat4 modelMatrix);
			
			~hmigraphicsobject();
			
		protected:
		
		
		private:
		
	};
}

#endif
