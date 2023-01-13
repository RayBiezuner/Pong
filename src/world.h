#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <string>
#include <vector>
#include "shader.h"

using std::string, glm::vec2, std::vector;

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

struct Digit
{
    int number;
    vec2 coordinates, scale;
    vector<int> grid;
    Digit(int n, vec2 c, vec2 s) : number(n), coordinates(c), scale(s)
    {
        loadGrid(n);
    }
    void loadGrid(int n)
    {
        number = n;
        if (number == 0)
            grid = {1, 2, 3, 4, 6, 7, 9, 10, 12, 13, 14, 15};
        else if (number == 1)
            grid = {3, 6, 9, 12, 15};
        else if (number == 2)
            grid = {1, 2, 3, 6, 7, 8, 9, 10, 13, 14, 15};
        else if (number == 3)
            grid = {1, 2, 3, 6, 7, 8, 9, 12, 13, 14, 15};
        else if (number == 4)
            grid = {1, 3, 4, 6, 7, 8, 9, 12, 15};
        else if (number == 5)
            grid = {1, 2, 3, 4, 7, 8, 9, 12, 13, 14, 15};
        else if (number == 6)
            grid = {1, 2, 3, 4, 7, 8, 9, 10, 12, 13, 14, 15};
        else if (number == 7)
            grid = {1, 2, 3, 4, 7, 8, 9, 10, 12, 13, 14, 15};
        else if (number == 8)
            grid = {1, 2, 3, 4, 6, 7, 8, 9, 10, 12, 13, 14, 15};
        else if (number == 9)
            grid = {1, 2, 3, 4, 6, 7, 8, 9, 12, 15};
    }
    void increaseScore()
    {
        loadGrid(number + 1);
    }
    void show(Shader shader)
    {
        int x, y;
        for (auto g : grid)
        {

            if (g % 3 == 1)
                x = -1;
            else if (g % 3 == 2)
                x = 0;
            else
                x = 1;

            if (g / 3.f <= 1)
                y = 2;
            else if (g / 3.f <= 2)
                y = 1;
            else if (g / 3.f <= 3)
                y = 0;
            else if (g / 3.f <= 4)
                y = -1;
            else
                y = -2;

            shader.setVec2("uCoord", coordinates + scale.x * vec2(x, y));
            shader.setVec2("uScale", scale);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
};

class World
{
private:
    unsigned int VAO, VBO, EBO;
    Box line, player1, player2;
    Ball ball;
    Digit digit1, digit2;
    Shader mShader;

public:
    World();
    void loadBuffers();
    void inputMode(GLFWwindow *window);
    void loadBall();
    void loadScore();
    void draw();
};

#endif
