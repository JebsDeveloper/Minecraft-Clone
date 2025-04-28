#pragma once

#include <glad/glad.h>
#include <string>

class Texture {
public:
    Texture(const char* path);
    ~Texture();

    void bind(unsigned int unit = 0) const;

    std::string type;
    std::string path;

    int width;
    int height;

    unsigned int textureID;
};
