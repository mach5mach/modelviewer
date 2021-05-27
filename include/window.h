#ifndef WINDOW_H
#define WINDOW_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include <nlohmann/json.hpp>

#include <spdlog/spdlog.h>

using json = nlohmann::json;

class Window
{
	public:
		std::string name;
		int width;
		int height;
	
		Window()
		{
			this->name = "";
			this->width = -1;
			this->height = -1;
		}
	
		Window(json window)
		{
			this->name = window["name"];
			this->width = window["width"];
			this->height = window["height"];
		}
		
		void SetHint(int target, int hint)
		{
			glfwWindowHint(target, hint);		
		}
		
		bool Init()
		{
			return glfwInit();
		}
		
		void Create()
		{
			window = glfwCreateWindow(this->width, this->height, this->name.c_str(), NULL, NULL);
			
			if(!window)
			{
				spdlog::get("file")->error("Couldn't create a window");
				spdlog::get("console")->error("Couldn't create a window");
				//Window or OpenGL context creation failed
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
			
			glfwMakeContextCurrent(window);	
		}
		
		void SetErrorCallback(GLFWerrorfun callback)
		{
			glfwSetErrorCallback(callback);
		}
		
		void SetFramebufferSizeCallback(GLFWframebuffersizefun callback){
			glfwSetFramebufferSizeCallback(window, callback);		
		}
		
		void SetCursorPosCallback(GLFWcursorposfun callback)
		{
			glfwSetCursorPosCallback(window, callback);
		}
	
		void SetScrollCallback(GLFWcursorposfun callback)
		{
			glfwSetScrollCallback(window, callback);
		}		
		
		void SetKeyCallback(GLFWkeyfun callback)
		{
			glfwSetKeyCallback(window, callback);
		}
	
		void SetWindowCloseCallback(GLFWwindowclosefun callback)
		{
			glfwSetWindowCloseCallback(window, callback);
		}
		
		void SetInputMode(int mode, int value)
		{
			glfwSetInputMode(window, mode, value);
		}
		
		bool ShouldClose()
		{
			return glfwWindowShouldClose(window);
		}
		
		void SetWindowShouldClose(bool close)
		{
			glfwSetWindowShouldClose(window, close);
		}
		
		void Close()
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}
		
		int GetKey(int key)
		{
			return glfwGetKey(window, key);
		}

	//private:
		GLFWwindow* window = NULL;

};




#endif
