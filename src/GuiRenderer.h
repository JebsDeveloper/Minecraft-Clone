#pragma once

#include <glad/glad.h>

#include <map>

#include "Shader.h"
#include "Widget.h"

class GuiRenderer {
public:
	GuiRenderer(Shader &shader);
	~GuiRenderer();

	void initRenderData();
	void renderWidget(Widget &widget, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
private:
	Shader shader;

	unsigned int VAO;
    unsigned int VBO;
};
