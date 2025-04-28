#include "Block.h"

Block::Block(BlockType type, glm::vec3 position) {
    this -> type = type;
    this -> position = position;

    auto uv = [](int x, int y) -> BlockFaceTexCoords {
        constexpr float size = 1.0f / 16.0f;
    
        glm::vec2 topLeft = {x * size, 1.0f - (y + 1) * size};
        glm::vec2 bottomRight = {(x + 1) * size, 1.0f - y * size};

        return BlockFaceTexCoords{topLeft, bottomRight};
    };     

    switch (type) {
        case GRASS:
            this -> texture_top = uv(0, 0);
            this -> texture_bottom = uv(2, 0);
            this -> texture_left = this -> texture_right = this -> texture_front = this -> texture_back = uv(1, 0);

            break;
        case DIRT:
            this -> texture_top = this -> texture_bottom = this -> texture_left = this -> texture_right = this -> texture_front = this -> texture_back = uv(2, 0);

            break;
        case STONE:
            this -> texture_top = this -> texture_bottom = this -> texture_left = this -> texture_right = this -> texture_front = this -> texture_back = uv(0, 1);

            break;
        case WATER:
            this -> texture_top = this -> texture_bottom = this -> texture_left = this -> texture_right = this -> texture_front = this -> texture_back = uv(1, 1);

            break;
        case GLASS:
            this  -> texture_top = this -> texture_bottom = this -> texture_left = this -> texture_right = this -> texture_front = this -> texture_back = uv(3, 0);

            break;
    }
}

Block::~Block() {

}
