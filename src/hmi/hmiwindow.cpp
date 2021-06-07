#include <hmi/hmiwindow.h>

#include <spdlog/spdlog.h>

hmi::hmiwindow::hmiwindow()
{
	this->name = "";
	this->width = -1;
	this->height = -1;
}
		
hmi::hmiwindow::hmiwindow(json config)
{
	spdlog::get("file")->trace("hmiwindow constructor");
	spdlog::get("console")->trace("hmiwindow constructor");
	
	spdlog::get("file")->trace("hmiwindow config {}", config.dump());
	spdlog::get("console")->trace("hmiwindow config {}", config.dump());

	this->config = config;

	this->name = config["name"];
	this->width = config["width"];
	this->height = config["height"];
}
			
void hmi::hmiwindow::SetHint(int target, int hint)
{
	spdlog::get("file")->trace("hmiwindow sethint target {} hint {}", target, hint);
	spdlog::get("console")->trace("hmiwindow sethint target {} hint {}", target, hint);

	glfwWindowHint(target, hint);		
}
			
bool hmi::hmiwindow::Init()
{
	spdlog::get("file")->trace("hmiwindow init");
	spdlog::get("console")->trace("hmiwindow init");

	return glfwInit();
}
			
void hmi::hmiwindow::Create()
{
	spdlog::get("file")->trace("hmiwindow create");
	spdlog::get("console")->trace("hmiwindow create");

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
	spdlog::get("file")->trace("hmiwindow seterrorcallback");
	spdlog::get("console")->trace("hmiwindow seterrorcallback");

	glfwSetErrorCallback(callback);
}

void hmi::hmiwindow::SetFramebufferSizeCallback(GLFWframebuffersizefun callback){
	spdlog::get("file")->trace("hmiwindow setframebuffersizecallback");
	spdlog::get("console")->trace("hmiwindow setframebuffersizecallback");

	glfwSetFramebufferSizeCallback(glfwwindow, callback);		
}

void hmi::hmiwindow::SetCursorPosCallback(GLFWcursorposfun callback)
{
	spdlog::get("file")->trace("hmiwindow setcursorposcallback");
	spdlog::get("console")->trace("hmiwindow setcursorposcallback");

	glfwSetCursorPosCallback(glfwwindow, callback);
}

void hmi::hmiwindow::SetScrollCallback(GLFWcursorposfun callback)
{
	spdlog::get("file")->trace("hmiwindow setscrollcallback");
	spdlog::get("console")->trace("hmiwindow setscrollcallback");

	glfwSetScrollCallback(glfwwindow, callback);
}		

void hmi::hmiwindow::SetKeyCallback(GLFWkeyfun callback)
{
	spdlog::get("file")->trace("hmiwindow setkeycallback");
	spdlog::get("console")->trace("hmiwindow setkeycallback");

	glfwSetKeyCallback(glfwwindow, callback);
}

void hmi::hmiwindow::SetWindowCloseCallback(GLFWwindowclosefun callback)
{
	spdlog::get("file")->trace("hmiwindow setwindowclosecallback");
	spdlog::get("console")->trace("hmiwindow setwindowclosecallback");

	glfwSetWindowCloseCallback(glfwwindow, callback);
}

void hmi::hmiwindow::SetInputMode(int mode, int value)
{
	spdlog::get("file")->trace("hmiwindow setinputmode mode {} value {}", mode, value);
	spdlog::get("console")->trace("hmiwindow setinputmode mode {} value {}", mode, value);

	glfwSetInputMode(glfwwindow, mode, value);
}

bool hmi::hmiwindow::ShouldClose()
{
	return glfwWindowShouldClose(glfwwindow);
}

void hmi::hmiwindow::SetWindowShouldClose(bool close)
{
	spdlog::get("file")->trace("hmiwindow setwindowshouldclose {}", close);
	spdlog::get("console")->trace("hmiwindow setwindowshouldclose {}", close);

	glfwSetWindowShouldClose(glfwwindow, close);
}

void hmi::hmiwindow::Close()
{
	spdlog::get("file")->trace("hmiwindow close");
	spdlog::get("console")->trace("hmiwindow close");

	glfwDestroyWindow(glfwwindow);
	glfwTerminate();
}

int hmi::hmiwindow::GetKey(int key)
{
	return glfwGetKey(glfwwindow, key);
}
