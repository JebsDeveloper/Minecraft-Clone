#pragma once

#include "Camera.h"
#include "BlockRenderer.h"

struct Globals {
    static Camera* camera;
    static BlockRenderer* blockRenderer;
};
