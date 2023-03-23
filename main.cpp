#include <glad/glad.h>
#include <GLFW/glfw3.h>

// #include "src/shader.h"
#include "src/world.h"

#include <iostream>
#include <ctime>

using std::srand, std::time;

int main()
{
    srand(time(0));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Pong", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    World world;
    world.loadBuffers();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.11f, 0.3f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        world.inputMode(window);
        world.loadBall();
        world.loadScore();
        world.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    /*
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO); */

    glfwTerminate();

    return 0;
}
