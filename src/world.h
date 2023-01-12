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

struct Ball
{
    vec2 coordinates;
    vec2 scale;
    vec2 direction;
    void move()
    {
        coordinates += direction;
        if (coordinates.y >= 0.95f)
        {
            coordinates.y == 0.95f;
            direction.y *= -1;
        }
        else if (coordinates.y <= -0.95f)
        {
            coordinates.y == -0.95f;
            direction.y *= -1;
        }
    }
    void collision(Box player, int p)
    {
        vec2 lPlayer = player.coordinates + vec2(-0.05f, 0.15f);
        lPlayer.x *= 3.0f / 4.0f;
        vec2 rPlayer = player.coordinates + vec2(0.05f, -0.15f);
        rPlayer.x *= 3.0f / 4.0f;
        vec2 lBall = coordinates + vec2(-0.05f, 0.05f);
        lBall.x *= 3.0f / 4.0f;
        vec2 rBall = coordinates + vec2(0.05f, -0.05f);
        rBall.x *= 3.0f / 4.0f;

        bool overlap;

        // ONE RECTANGLE IS TO THE LEFT OF THE OTHER
        if (lPlayer.x > rBall.x || lBall.x > rPlayer.x)
        {
            overlap = false;
        }
        // ONE RECTANGLE IS ON THE TOP OF THE OTHER
        else if (lPlayer.y < rBall.y || lBall.y < rPlayer.y)
        {
            overlap = false;
        }
        // THERE IS A OVERLAP
        else
            overlap = true;

        if (overlap)
            direction.x *= -1;
    }
};

class World
{
private:
    unsigned int VAO, VBO, EBO;
    Box line, player1, player2;
    Ball ball;
    Shader mShader;

public:
    World();
    void loadBuffers();
    void inputMode(GLFWwindow *window);
    void loadBall();
    void draw();
};

#endif
