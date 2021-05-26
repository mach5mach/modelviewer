
// C program to demonstrate
// drawing a circle using
// OpenGL

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <nlohmann/json.hpp>

#include <window.h>
#include <scene.h>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

#include <spdlog/spdlog.h>
#include "spdlog/sinks/rotating_file_sink.h"

using json = nlohmann::json;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput();

Window win;
vector<Scene> scenes;
Scene* currentScene = NULL;

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
	std::cout << "Closing window" << std::endl;
}

void error_callback(int error, const char* description)
{
	std::cout << "Error: " << description << std::endl;
}
 
void initialize_loggers()
{
	auto max_size = 1048576 * 5;
    	auto max_files = 3;
	auto logger = spdlog::rotating_logger_mt("file", "./logs/modelviewer.txt", max_size, max_files);
}
 
int main (int argc, char** argv)
{
	initialize_loggers();

	spdlog::get("file")->info("Welcome to spdlog!");

	json jsonScene;
	if(argc > 1)
	{
		std::ifstream inputfile(argv[1]);
		
		inputfile >> jsonScene;
		
		std::cout << jsonScene << std::endl;
	}

	win = Window(jsonScene["window"]);
	
	win.SetHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	win.SetHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	win.SetHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	win.SetErrorCallback(error_callback);
	
	if(!win.Init())
	{
		std::cout << "Couldn't initialize glfw" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	win.Create();
	
	win.SetFramebufferSizeCallback(framebuffer_size_callback);
	win.SetCursorPosCallback(mouse_callback);
	win.SetScrollCallback(scroll_callback);	
	//win.SetKeyCallback(key_callback);
	win.SetWindowCloseCallback(window_close_callback);
	
	win.SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	for(json::iterator it = jsonScene["scenes"].begin(); it != jsonScene["scenes"].end(); ++it)
	{
		Scene scene(*it);
		scenes.push_back(scene);
	}	
	
	currentScene = &(scenes[0]);
	currentScene->Init();
	
	for(int i = 0; i < currentScene->model->meshes.size(); i++)
	{
		std::cout << "Loaded mesh " << currentScene->model->meshes[i].name << std::endl;
	}
	
	int width, height;
	glfwGetWindowSize(win.window, &width, &height);

	lastX = width / 2.0f;
	lastY = height / 2.0f;	
		
	while(!win.ShouldClose())
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		currentScene->Render(win);

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
		//move this somewhere else
		int hsindex = currentScene->model->GetMeshIndexByName("Hamstring_Hamstring_Muscle");
		int quadindex = currentScene->model->GetMeshIndexByName("Quad_Quad_Muscle");
		int femurindex = currentScene->model->GetMeshIndexByName("Femur_Femur_Bone");
		int tibiaindex = currentScene->model->GetMeshIndexByName("Tibia_Tibia_Bone");
	
		if(win.GetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			std::cout << "HS Index: " << hsindex << std::endl;
			//hamstring contract
			if(hsindex != -1 && quadindex != -1)
			{
				std::cout << "Knee flexion" << std::endl;
			
				currentScene->model->meshes[hsindex].scale[1] *= 0.9;
				std::cout << "HS scale: " << currentScene->model->meshes[hsindex].scale[1] << std::endl;
				
				currentScene->model->meshes[quadindex].scale[1] /= 0.9;
				std::cout << "Quad scale: " << currentScene->model->meshes[quadindex].scale[1] << std::endl;
				
				currentScene->model->meshes[tibiaindex].rotation = glm::vec3(0.0, 0.0, 1.0);
				currentScene->model->meshes[tibiaindex].rotationDeg -= 10.0f;
				std::cout << "Tibia rotation: " << currentScene->model->meshes[tibiaindex].rotationDeg << " about " << currentScene->model->meshes[tibiaindex].rotation[0] << ", " << currentScene->model->meshes[tibiaindex].rotation[1] << ", " << currentScene->model->meshes[tibiaindex].rotation[2] << std::endl;
			}
		}
		if(win.GetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			std::cout << "Quad Index: " << quadindex << std::endl;
			//quad contract
			if(hsindex != -1 && quadindex != -1)
			{
				std::cout << "Knee extension" << std::endl;
			
				currentScene->model->meshes[quadindex].scale[1] *= 0.9;
				std::cout << "Quad scale: " << currentScene->model->meshes[quadindex].scale[1] << std::endl;
				
				currentScene->model->meshes[hsindex].scale[1] /= 0.9;
				std::cout << "HS scale: " << currentScene->model->meshes[hsindex].scale[1] << std::endl;
				
				currentScene->model->meshes[femurindex].rotation = glm::vec3(0.0, 0.0, 1.0);
				currentScene->model->meshes[tibiaindex].rotationDeg += 10.0f;
				std::cout << "Tibia rotation: " << currentScene->model->meshes[tibiaindex].rotationDeg << " about " << currentScene->model->meshes[tibiaindex].rotation[0] << ", " << currentScene->model->meshes[tibiaindex].rotation[1] << ", " << currentScene->model->meshes[tibiaindex].rotation[2] << std::endl;
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
