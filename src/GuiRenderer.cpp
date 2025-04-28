#include "GuiRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

GuiRenderer::GuiRenderer(Shader &shader): shader(shader) {

}

GuiRenderer::~GuiRenderer() {
	glDeleteVertexArrays(1, &this -> VAO);
	glDeleteBuffers(1, &this -> VBO);
}


void GuiRenderer::initRenderData() {
	float vertices[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this -> VAO);
	glGenBuffers(1, &this -> VBO);

	glBindVertexArray(this -> VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this -> VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GuiRenderer::renderWidget(Widget &widget, glm::vec3 color) {
	this -> shader.use();

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(widget.position, 0.0f));
	model = glm::translate(model, glm::vec3(widget.size.x * 0.5f, widget.size.y * 0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(widget.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(widget.size.x * -0.5f, widget.size.y * -0.5f, 0.0f));
	model = glm::scale(model, glm::vec3(widget.size, 1.0f));

	this -> shader.setMat4("model", model);
	this -> shader.setVec3("spriteColor", color);

	widget.texture.bind();

	glBindVertexArray(this -> VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
