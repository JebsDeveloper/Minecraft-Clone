#pragma once

#include <glm/glm.hpp>

struct BlockFaceTexCoords {
    glm::vec2 topLeft;
    glm::vec2 bottomRight;
};

enum BlockType {
    GRASS,
    DIRT,
    STONE,
    WATER,
    GLASS
};

class Block {
public:
    Block(BlockType type, glm::vec3 position);
    ~Block();

    glm::vec3 position;
    BlockType type;

    BlockFaceTexCoords texture_top;
    BlockFaceTexCoords texture_bottom;
    BlockFaceTexCoords texture_left;
    BlockFaceTexCoords texture_right;
    BlockFaceTexCoords texture_front;
    BlockFaceTexCoords texture_back;
};
