#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class Window {
public:
	Window(unsigned int width, unsigned int height, std::string title);
	~Window();

	void init();
	void update();
	void cleanup();

	unsigned int getWidth();
	unsigned int getHeight();

	bool windowShouldClose();
	GLFWwindow* getWindow();
	
	static void inputPerFrame(GLFWwindow* window, float deltaTime);
private:
	unsigned int width;
	unsigned int height;
	std::string title;

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mousePositionCallback(GLFWwindow* window, double posX, double posY);
	static void mouseScrollCallback(GLFWwindow* window, double offsetX, double offsetY);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	static float lastX;
	static float lastY;
	static bool firstMouse;

	GLFWwindow* window;
};
