#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <string>
#include "shader.h"

using std::string, glm::vec2;

struct Box
{
    vec2 coordinates;
    vec2 scale;
    void move(string dir)
    {
        if (dir == "UP")
            coordinates += vec2(0.f, 0.03f);
        else
            coordinates -= vec2(0.f, 0.03f);
        if (coordinates.y >= 0.85f)
            coordinates.y = 0.85f;
        else if (coordinates.y <= -0.85f)
            coordinates.y = -0.85f;
    }
};

class World
{
private:
    unsigned int VAO, VBO, EBO;
    Box line, player1, player2;
    Shader mShader;

public:
    World();
    void loadBuffers();
    void inputMode(GLFWwindow *window);
    void draw();
};

#endif
