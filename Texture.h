#pragma once
#include <glad/glad.h>

class Texture
{
public:
    unsigned int ID = 0;

    Texture(const char *path);
    ~Texture();

    void bind(int slot = 0) const;
};