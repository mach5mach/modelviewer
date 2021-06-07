#ifndef HMIWINDOW_H
#define HMIWINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <nlohmann/json.hpp>

#include <spdlog/spdlog.h>

#include <string>
#include <iostream>

using json = nlohmann::json;

namespace hmi
{
	class hmiwindow
	{
		public:
			json config;
		
			std::string name;
			int width;
			int height;
		
			hmiwindow();
		
			hmiwindow(json config);
			
			void SetHint(int target, int hint);
			
			bool Init();
			
			void Create();
			
			void SetErrorCallback(GLFWerrorfun callback);
			
			void SetFramebufferSizeCallback(GLFWframebuffersizefun callback);
			
			void SetCursorPosCallback(GLFWcursorposfun callback);
		
			void SetScrollCallback(GLFWcursorposfun callback);	
			
			void SetKeyCallback(GLFWkeyfun callback);
		
			void SetWindowCloseCallback(GLFWwindowclosefun callback);
			
			void SetInputMode(int mode, int value);
			
			bool ShouldClose();
			
			void SetWindowShouldClose(bool close);
			
			void Close();
			
			int GetKey(int key);

		//private:
			GLFWwindow* glfwwindow = NULL;

	};
}

#endif
