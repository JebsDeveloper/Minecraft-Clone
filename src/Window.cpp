#include "Window.h"

#include <stdexcept>
#include <iostream>

#include "Globals.h"

#define REMOVE_IMGUI 0

#if REMOVE_IMGUI == 0
	#include "imgui.h"
	#include "backends/imgui_impl_glfw.h"
	#include "backends/imgui_impl_opengl3.h"
#endif

// Change based on window size
float Window::lastX = 400.0f;
float Window::lastY = 300.0f;
bool  Window::firstMouse = true;

Window::Window(unsigned int width, unsigned int height, std::string title) {
	this -> width = width;
	this -> height = height;
	this -> title = title;
}

Window::~Window() {

}

void Window::init() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	this -> window = glfwCreateWindow(this -> width, this -> height, this -> title.c_str(), nullptr, nullptr);

	if (this -> window == nullptr) {
		throw std::runtime_error("Failed to create GLFW window.");
	}

	glfwMakeContextCurrent(this -> window);

	//glfwSetWindowAspectRatio(this -> window, 16, 9);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(this -> window, Window::framebufferSizeCallback);
	glfwSetKeyCallback(this -> window, Window::keyCallback);
	glfwSetCursorPosCallback(this -> window, Window::mousePositionCallback);
	glfwSetScrollCallback(this -> window, Window::mouseScrollCallback);
	glfwSetMouseButtonCallback(this -> window, Window::mouseButtonCallback);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD.");
	}

	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if REMOVE_IMGUI == 0
	ImGui::CreateContext();

	ImGuiIO &io = ImGui::GetIO();
	(void) io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(this -> window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
#endif
}

void Window::update() {
#if REMOVE_IMGUI == 0
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// ImGui

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif

	glfwSwapBuffers(this -> window);
	glfwPollEvents();
}

void Window::cleanup() {
#if REMOVE_IMGUI == 0
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif

	glfwTerminate();
}

unsigned int Window::getWidth() {
	return this -> width;
}

unsigned int Window::getHeight() {
	return this -> height;
}

bool Window::windowShouldClose() {
	return glfwWindowShouldClose(this -> window);
}

GLFWwindow* Window::getWindow() {
	return this -> window;
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, true);
		}
	}
}

void Window::inputPerFrame(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_W)) {
		Globals::camera -> keyboardInput(FORWARD, deltaTime);
	} else if (glfwGetKey(window, GLFW_KEY_S)) {
		Globals::camera -> keyboardInput(BACKWARD, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A)) {
		Globals::camera -> keyboardInput(LEFT, deltaTime);
	} else if (glfwGetKey(window, GLFW_KEY_D)) {
		Globals::camera -> keyboardInput(RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE)) {
		Globals::camera -> keyboardInput(UP, deltaTime);
	} else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
		Globals::camera -> keyboardInput(DOWN, deltaTime);
	}
}

void Window::mousePositionCallback(GLFWwindow* window, double posX, double posY) {
	if (firstMouse) {
        lastX = (float) posX;
        lastY = (float) posY;
        firstMouse = false;
    }

    float offsetX = (float) posX - lastX;
    float offsetY = lastY - (float) posY;  

    lastX = (float) posX;
    lastY = (float) posY;

	Globals::camera -> mouseInput(offsetX, offsetY);
}

void Window::mouseScrollCallback(GLFWwindow* window, double offsetX, double offsetY) {
	Globals::camera -> mouseScroll(offsetY);
}

void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			Globals::blockRenderer -> breakBlock(Globals::camera -> position, Globals::camera -> front);
		} else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			Globals::blockRenderer -> placeBlock(Globals::camera -> position, Globals::camera -> front);
		}
	}
}
