#ifndef HMISCENE_H
#define HMISCENE_H

#include <hmi/hmianatomyobject.h>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <nlohmann/json.hpp>


#include <string>
#include <vector>


using json = nlohmann::json;

namespace hmi
{
	class hmiwindow;

	class hmiscene
	{
		public:
			json config;
		
			int id;
			std::string name;
			glm::vec4 clearcolor;
			Camera* camera;
			Shader* shader;
			Model* model;
			vector<hmianatomyobject> anatObjs;	
		
			hmiscene();
		
			hmiscene(json config);
			
			void Init();
			
			void Render(hmiwindow* window);
			
			void ClearColor(glm::vec4 color);
		private:
			std::string vertShaderFileName;
			std::string geomShaderFileName;
			std::string fragShaderFileName;
			
			std::string modelFileName;
			glm::vec3 modelScale;
			glm::vec3 modelPosition;
			
			glm::vec3 cameraPosition;
			glm::vec2 cameraClipping;

	};

}


#endif
