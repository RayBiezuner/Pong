#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "world.h"
#include "glm/gtc/random.hpp"

using std::string, glm::vec2, glm::circularRand;

float vertices[] = {
    0.5f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f,
    -0.5f, 0.5f};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3};

World::World() : mShader("shaders/shader.vs", "shaders/shader.fs"),
                 digit1(0, {-0.3f, 0.8f}, {0.05f, 0.05f}), digit2(0, {0.3f, 0.8f}, {0.05f, 0.05f})
{
    loadBuffers();
    player1 = {{-0.95f, 0.f}, {0.1f, 0.3f}};
    player2 = {{0.95f, 0.f}, {0.1f, 0.3f}};
    line = {{0.0f, 0.0f}, {0.03f, 2.0f}};

    ball = {{0.f, 0.f}, {0.1f, 0.1f}, 0.01f * circularRand(1.f)};
}

void World::loadBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
}

void World::inputMode(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        player1.move("DOWN");
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        player1.move("UP");
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        player2.move("DOWN");
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        player2.move("UP");
    }
}

void World::loadBall()
{
    ball.move();
    if (ball.coordinates.x <= 0.f)
        ball.collision(player1, 1);
    else
        ball.collision(player2, 2);

    std::cout << ball.coordinates.x << std::endl;
    if (ball.coordinates.x <= -4.f / 3.f)
        digit1.increaseScore();
    else if (ball.coordinates.x >= 4.f / 3.f)
        digit1.increaseScore();
}

void World::loadScore()
{
    digit1.show(mShader);
    digit2.show(mShader);
}
void World::draw()
{
    mShader.use();
    glBindVertexArray(VAO);

    mShader.setVec2("uCoord", line.coordinates);
    mShader.setVec2("uScale", line.scale);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // DRAW PLAYER1
    mShader.setVec2("uCoord", player1.coordinates);
    mShader.setVec2("uScale", player1.scale);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // DRAW PLAYER2
    mShader.setVec2("uCoord", player2.coordinates);
    mShader.setVec2("uScale", player2.scale);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // DRAW SCORE

    // DRAW BALL
    mShader.setVec2("uCoord", ball.coordinates);
    mShader.setVec2("uScale", ball.scale);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
