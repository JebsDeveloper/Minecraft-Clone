#include "BlockRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

BlockRenderer::BlockRenderer(Shader &shader): shader(shader) {

}

BlockRenderer::~BlockRenderer() {
	glDeleteVertexArrays(1, &this -> VAO);
}

void BlockRenderer::initRenderData() {
    glGenVertexArrays(1, &this -> VAO);
    glGenBuffers(1, &this -> VBO);
    glGenBuffers(1, &this -> instanceVBO);

    float cubeVertices[] = {
        0,0,0, 1,0,0, 1,1,0, 1,1,0, 0,1,0, 0,0,0,
        1,0,1, 0,0,1, 0,1,1, 0,1,1, 1,1,1, 1,0,1,
        0,0,1, 0,0,0, 0,1,0, 0,1,0, 0,1,1, 0,0,1,
        1,0,0, 1,0,1, 1,1,1, 1,1,1, 1,1,0, 1,0,0,
        0,1,0, 1,1,0, 1,1,1, 1,1,1, 0,1,1, 0,1,0,
        0,0,1, 1,0,1, 1,0,0, 1,0,0, 0,0,0, 0,0,1
    };

    glBindVertexArray(this -> VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this -> VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    glBindBuffer(GL_ARRAY_BUFFER, this -> instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BlockInstance), (void*) 0);
    glVertexAttribDivisor(1, 1);

    for (unsigned char i = 0; i < 6; i++) {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer(2 + i, 2, GL_FLOAT, GL_FALSE, sizeof(BlockInstance), (void*) (sizeof(glm::vec3) + i * sizeof(glm::vec2)));
        glVertexAttribDivisor(2 + i, 1);
    }

    glBindVertexArray(0);
}

void BlockRenderer::addBlock(const Block &block) {
	BlockInstance blockInstance;
    blockInstance.position = block.position;

    blockInstance.uvs[0] = block.texture_back.topLeft;
    blockInstance.uvs[1] = block.texture_front.topLeft;
    blockInstance.uvs[2] = block.texture_left.topLeft;
    blockInstance.uvs[3] = block.texture_right.topLeft;
    blockInstance.uvs[4] = block.texture_top.topLeft;
    blockInstance.uvs[5] = block.texture_bottom.topLeft;

    this -> blockInstances[glm::ivec3(block.position)] = blockInstance;
}

void BlockRenderer::render() {
	this -> shader.use();

    std::vector<BlockInstance> instanceData;
    instanceData.reserve(this -> blockInstances.size());

    for (const auto &pair : this -> blockInstances) {
        instanceData.push_back(pair.second);
    }

	glBindBuffer(GL_ARRAY_BUFFER, this -> instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, this -> blockInstances.size() * sizeof(BlockInstance), instanceData.data(), GL_DYNAMIC_DRAW);

	glBindVertexArray(this -> VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, this -> blockInstances.size());
    glBindVertexArray(0);
}

void BlockRenderer::breakBlock(glm::vec3 playerPosition, glm::vec3 direction) {
    glm::vec3 rayOrigin = playerPosition;
    glm::vec3 rayDirection = glm::normalize(direction);

    constexpr const float maxDistance = 6.0f;
    constexpr const float stepSize = 0.05f;

    float currentDistance = 0.0f;

    while (currentDistance < maxDistance) {
        glm::vec3 currentPos = rayOrigin + rayDirection * currentDistance;
        glm::ivec3 blockPos = glm::floor(currentPos);

        auto it = this -> blockInstances.find(blockPos);

        if (it != this -> blockInstances.end()) {
            this -> blockInstances.erase(it);

            break;
        }

        currentDistance += stepSize;
    }
}

void BlockRenderer::placeBlock(glm::vec3 playerPosition, glm::vec3 direction) {
    glm::vec3 rayOrigin = playerPosition;
    glm::vec3 rayDirection = glm::normalize(direction);

    constexpr const float maxDistance = 6.0f;
    constexpr const float stepSize = 0.01f;
    float currentDistance = 0.0f;

    glm::ivec3 previousBlock = glm::floor(rayOrigin);

    while (currentDistance < maxDistance) {
        glm::vec3 currentPos = rayOrigin + rayDirection * currentDistance;
        glm::ivec3 currentBlock = glm::floor(currentPos);

        if (this -> blockInstances.find(currentBlock) != this -> blockInstances.end()) {
            Block block = Block(GLASS, previousBlock);
            this -> addBlock(block);

            break;
        }

        previousBlock = currentBlock;
        currentDistance += stepSize;
    }
}

std::vector<float> BlockRenderer::generateBlockVertices(const Block &block) {
	const BlockFaceTexCoords &top = block.texture_top;
    const BlockFaceTexCoords &bottom = block.texture_bottom;
    const BlockFaceTexCoords &left = block.texture_left;
    const BlockFaceTexCoords &right = block.texture_right;
    const BlockFaceTexCoords &front = block.texture_front;
    const BlockFaceTexCoords &back = block.texture_back;

	glm::vec3 p[] = {
        {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
        {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}
    };

	auto face = [](glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, glm::vec2 uvMin, glm::vec2 uvMax) {
        return std::vector<float>{
            a.x, a.y, a.z, uvMin.x, uvMin.y,
            b.x, b.y, b.z, uvMax.x, uvMin.y,
            c.x, c.y, c.z, uvMax.x, uvMax.y,

            c.x, c.y, c.z, uvMax.x, uvMax.y,
            d.x, d.y, d.z, uvMin.x, uvMax.y,
            a.x, a.y, a.z, uvMin.x, uvMin.y
        };
    };

	std::vector<float> vertices;

    auto add = [&](std::vector<float> f) {
        vertices.insert(vertices.end(), f.begin(), f.end());
    };

	add(face(p[0], p[1], p[2], p[3], back.topLeft, back.bottomRight));
    add(face(p[5], p[4], p[7], p[6], front.topLeft, front.bottomRight));
    add(face(p[4], p[0], p[3], p[7], left.topLeft, left.bottomRight));
    add(face(p[1], p[5], p[6], p[2], right.topLeft, right.bottomRight));
    add(face(p[3], p[2], p[6], p[7], top.topLeft, top.bottomRight));
    add(face(p[4], p[5], p[1], p[0], bottom.topLeft, bottom.bottomRight));

	return vertices;
}
