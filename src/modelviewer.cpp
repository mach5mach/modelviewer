#include <hmi/hmiwindow.h>
#include <hmi/hmiscene.h>
#include <hmi/hmimuscles.h>
#include <hmi/hmibones.h>


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <nlohmann/json.hpp>


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

using json = nlohmann::json;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput();

hmi::hmiwindow win;
vector<hmi::hmiscene> scenes;
hmi::hmiscene* currentScene = NULL;

float lastX;
float lastY;
bool firstMouse = true;


float deltaTime = 0.0f;
float lastFrame = 0.0f;
 
float translatex, translatey, movement; 

void pollkeys()
{
		if (win.GetKey(GLFW_KEY_LEFT))
			translatex -= movement;
		if (win.GetKey(GLFW_KEY_RIGHT))
			translatex += movement;
		if (win.GetKey(GLFW_KEY_DOWN))
			translatey -= movement;
		if (win.GetKey(GLFW_KEY_UP))
			translatey += movement;
}

void window_close_callback(GLFWwindow* window)
{
	spdlog::get("file")->info("Closing window");
	spdlog::get("console")->info("Closing window");
}

void error_callback(int error, const char* description)
{
	spdlog::get("file")->error("Error: {}", description);
	spdlog::get("console")->error("Error: {}", description);
}
 
void initialize_loggers(json log)
{
	auto max_size = 1048576 * 5;
    	auto max_files = 3;
	auto logger = spdlog::rotating_logger_mt("file", log["filename"], max_size, max_files);
	
	auto console = spdlog::stdout_color_mt("console");
	
	spdlog::set_level(log["level"]);
	
	spdlog::get("file")->trace("file logger initialized");
	spdlog::get("console")->trace("console logger initialized");
}
 
int main (int argc, char** argv)
{
	std::cout << "program started" << std::endl;

	json config;
	if(argc == 2)
	{
		try{		
			std::ifstream inputfile(argv[1]);
			
			inputfile >> config;
			
			std::cout << argv[1] << " loaded successfully" << std::endl;
		}
		catch(const std::exception&)
		{
			std::cout << "Failed to load json file: " << argv[1] << std::endl;
			std::cout << "Exiting" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		std::cout << "Must specify exactly one json file" << std::endl;
		std::cout << "Exiting" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	if(config.contains("general"))
	{
		json general = config["general"];
		
		if(general.contains("log"))
		{
			initialize_loggers(general["log"]);
		}
	}

	spdlog::get("file")->debug(config.dump());
	spdlog::get("console")->debug(config.dump());

	win = hmi::hmiwindow(config["window"]);
	
	win.SetHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	win.SetHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	win.SetHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	win.SetErrorCallback(error_callback);
	
	if(!win.Init())
	{
		spdlog::get("file")->error("Couldn't initialize glfw");
		spdlog::get("console")->error("Couldn't initialize glfw");
		exit(EXIT_FAILURE);
	}
	
	win.Create();
	
	win.SetFramebufferSizeCallback(framebuffer_size_callback);
	win.SetCursorPosCallback(mouse_callback);
	win.SetScrollCallback(scroll_callback);	
	//win.SetKeyCallback(key_callback);
	win.SetWindowCloseCallback(window_close_callback);
	
	win.SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	for(json::iterator it = config["scenes"].begin(); it != config["scenes"].end(); ++it)
	{
		hmi::hmiscene scene(*it);
		scenes.push_back(scene);
	}	
	
	currentScene = &(scenes[0]);
	currentScene->Init();
	
	for(size_t i = 0; i < currentScene->model->meshes.size(); i++)
	{
		spdlog::get("file")->debug(currentScene->model->meshes[i].name);
		spdlog::get("console")->debug(currentScene->model->meshes[i].name);
	}
	
	int width, height;
	glfwGetWindowSize(win.glfwwindow, &width, &height);

	lastX = width / 2.0f;
	lastY = height / 2.0f;	
		
	while(!win.ShouldClose())
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		currentScene->Render(&win);

		pollkeys();
		
		// input
		// -----
		processInput();
	}
     
	win.Close();
	
	exit(EXIT_SUCCESS);
}

void processInput()
{
	if(currentScene != NULL){
		float contractAmount = 0.005f;
		float rotateAmount = 10.0f;
		glm::vec3 rotation(0.0f, 0.0f, 1.0f);
	
		//move this somewhere else
		hmi::hmihamstring* hs = dynamic_cast<hmi::hmihamstring*>(currentScene->GetAnatomyObject("hamstring"));
		hmi::hmiquad* quad = dynamic_cast<hmi::hmiquad*>(currentScene->GetAnatomyObject("quad"));
		//hmi::hmifemur* femur = currentScene->GetAnatomyObject("femur");
		hmi::hmitibia* tibia = dynamic_cast<hmi::hmitibia*>(currentScene->GetAnatomyObject("tibia"));
	
		if(win.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
		{			
			//hamstring contract
			if(hs != nullptr && quad != nullptr && tibia != nullptr)
			{
				spdlog::get("file")->debug("Knee flexion");
				spdlog::get("console")->debug("Knee flexion");
							
				hs->contract(contractAmount);
				
				quad->relax(contractAmount);
				
				tibia->rotate(-rotateAmount, rotation);
			}
		}
		if(win.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			//quad contract
			if(hs != nullptr && quad != nullptr && tibia != nullptr)
			{
				spdlog::get("file")->debug("Knee extension");
				spdlog::get("console")->debug("Knee extension");
			
				hs->relax(contractAmount);
				
				quad->contract(contractAmount);
				
				tibia->rotate(rotateAmount, rotation);
			}
		}
	}
	

    if (win.GetKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        win.SetWindowShouldClose(true);

    if (win.GetKey(GLFW_KEY_W) == GLFW_PRESS)
        currentScene->camera->ProcessKeyboard(FORWARD, deltaTime);
    if (win.GetKey(GLFW_KEY_S) == GLFW_PRESS)
        currentScene->camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (win.GetKey(GLFW_KEY_A) == GLFW_PRESS)
        currentScene->camera->ProcessKeyboard(LEFT, deltaTime);
    if (win.GetKey(GLFW_KEY_D) == GLFW_PRESS)
        currentScene->camera->ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    currentScene->camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    currentScene->camera->ProcessMouseScroll(yoffset);
}
