#include "OpenGLPrj.hpp"
#include "Shader.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertShaderPath = "C:/Users/petar/OpenGLPrj/res/shaders/vert.vert";
const char* fragShaderPath = "C:/Users/petar/OpenGLPrj/res/shaders/frag.frag";
const char* texturePath = "C:/Users/petar/OpenGLPrj/res/textures/crate.png";

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(mWidth, mHeight, "Petar's Project", NULL, NULL);

    if (window == NULL) {
        cout << "Sorry... Your window failed..." << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Sorry.. GLAD failed you..." << endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float verticies[] = {
        -0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 0.0f,    0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f,    1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 1.0f,    1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,    0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Using absolute paths - change appropriately
    Shader shader = Shader(vertShaderPath, fragShaderPath);
    shader.use();

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int tWidth, tHeight, tChannels;
    unsigned char* tData = stbi_load(texturePath, &tWidth, &tHeight, &tChannels, 0);    
    if (tData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tWidth, tHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, tData);
        glGenerateMipmap(GL_TEXTURE_2D); }
    else
        cout << "Failed to load texture..." << endl;
    stbi_image_free(tData);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}