#pragma once

#include <glm/glm.hpp>

#include "Texture.h"

struct Widget {
    Widget(glm::vec2 position, float rotation, glm::vec2 size, Texture &texture): position(position), rotation(rotation), size(size), texture(texture) {}
    ~Widget() {}

    Texture &texture;

    glm::vec2 position;
    float rotation;
    glm::vec2 size;
};
