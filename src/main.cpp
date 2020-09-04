#include "OpenGLPrj.hpp"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = 
    "#version 400 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "void main() { \n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 400 core\n"
    "out vec4 fragColor;\n"
    "void main() { \n"
        "fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0);\n"
    "}\0";

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
        return -1;  }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Sorry.. GLAD failed you..." << endl;
        return -1;  }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float verticies[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VBO_ID;
    glGenBuffers(1, &VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    int success;        // success flag for shader compilation (bellow)
    char infoLog[512];  // if compile error -> print infoLog

    unsigned int vertexShader_ID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader_ID, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader_ID);
    
    glGetShaderiv(vertexShader_ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader_ID, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAIL" << endl;
        cout << infoLog << endl; }

    unsigned int fragmentShader_ID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader_ID, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader_ID);

    glGetShaderiv(fragmentShader_ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader_ID, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAIL" << endl;
        cout << infoLog << endl; }

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.3f, 0.2f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(50, 50, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}