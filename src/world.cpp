#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "world.h"
float vertices[] = {
    0.5f, 0.5f,
    0.5f, -0.5f,
    -0.5f, -0.5f,
    -0.5f, 0.5f};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3};

World::World() : mShader("shaders/shader.vs", "shaders/shader.fs")
{
    loadBuffers();
    line = {{0.0f, 0.0f}, {0.03f, 2.0f}};
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

void World::draw()
{
    mShader.use();
    glBindVertexArray(VAO);
    mShader.setVec2("uCoord", line.coordinates);
    mShader.setVec2("uScale", line.scale);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}