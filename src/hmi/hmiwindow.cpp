#include <hmi/hmiwindow.h>

hmi::hmiwindow::hmiwindow()
{
	this->name = "";
	this->width = -1;
	this->height = -1;
}
		
hmi::hmiwindow::hmiwindow(json config)
{
	this->name = config["name"];
	this->width = config["width"];
	this->height = config["height"];
}
			
void hmi::hmiwindow::SetHint(int target, int hint)
{
	glfwWindowHint(target, hint);		
}
			
bool hmi::hmiwindow::Init()
{
	return glfwInit();
}
			
void hmi::hmiwindow::Create()
{
	glfwwindow = glfwCreateWindow(this->width, this->height, this->name.c_str(), NULL, NULL);
	
	if(!glfwwindow)
	{
		spdlog::get("file")->error("Couldn't create a window");
		spdlog::get("console")->error("Couldn't create a window");
		//Window or OpenGL context creation failed
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(glfwwindow);	
}
			
void hmi::hmiwindow::SetErrorCallback(GLFWerrorfun callback)
{
	glfwSetErrorCallback(callback);
}

void hmi::hmiwindow::SetFramebufferSizeCallback(GLFWframebuffersizefun callback){
	glfwSetFramebufferSizeCallback(glfwwindow, callback);		
}

void hmi::hmiwindow::SetCursorPosCallback(GLFWcursorposfun callback)
{
	glfwSetCursorPosCallback(glfwwindow, callback);
}

void hmi::hmiwindow::SetScrollCallback(GLFWcursorposfun callback)
{
	glfwSetScrollCallback(glfwwindow, callback);
}		

void hmi::hmiwindow::SetKeyCallback(GLFWkeyfun callback)
{
	glfwSetKeyCallback(glfwwindow, callback);
}

void hmi::hmiwindow::SetWindowCloseCallback(GLFWwindowclosefun callback)
{
	glfwSetWindowCloseCallback(glfwwindow, callback);
}

void hmi::hmiwindow::SetInputMode(int mode, int value)
{
	glfwSetInputMode(glfwwindow, mode, value);
}

bool hmi::hmiwindow::ShouldClose()
{
	return glfwWindowShouldClose(glfwwindow);
}

void hmi::hmiwindow::SetWindowShouldClose(bool close)
{
	glfwSetWindowShouldClose(glfwwindow, close);
}

void hmi::hmiwindow::Close()
{
	glfwDestroyWindow(glfwwindow);
	glfwTerminate();
}

int hmi::hmiwindow::GetKey(int key)
{
	return glfwGetKey(glfwwindow, key);
}
