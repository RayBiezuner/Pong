#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include "shader.h"

using glm::vec2;

struct Box
{
    vec2 coordinates;
    vec2 scale;
};

class World
{
private:
    unsigned int VAO, VBO, EBO;
    Box line;
    Shader mShader;

public:
    World();
    void loadBuffers();
    void draw();
};

#endif
