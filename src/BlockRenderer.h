#pragma once

#include <glad/glad.h>

#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "Shader.h"
#include "Block.h"

struct BlockInstance {
	glm::vec3 position;
	glm::vec2 uvs[6];
};

class BlockRenderer {
public:
	BlockRenderer(Shader &shader);
	~BlockRenderer();

	void initRenderData();
	void addBlock(const Block &block);
	void render();

	void breakBlock(glm::vec3 playerPosition, glm::vec3 direction);
	void placeBlock(glm::vec3 playerPosition, glm::vec3 direction);
private:
	Shader shader;

	unsigned int VAO;
    unsigned int VBO;
	unsigned int instanceVBO;

	std::unordered_map<glm::ivec3, BlockInstance> blockInstances;
	std::vector<float> generateBlockVertices(const Block &block);

	std::vector<float> allVertices;
};
