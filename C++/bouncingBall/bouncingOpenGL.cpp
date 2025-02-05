#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector> 

// Vertex shader
const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 model;
void main() {
    gl_Position = model * vec4(aPos, 1.0);
})";

// Fragment shader
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Kırmızı
})";

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW başlatılamadı!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Circle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Pencere oluşturulamadı!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "error glad" << std::endl;
        return -1;
    }

    int numSegments = 100; 
    std::vector<float> vertices;

    float radius = 0.05f;
    for (int i = 0; i < numSegments; ++i) {
        float angle = 2.0f * 3.14159265358979f * float(i) / float(numSegments);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f); 
    }

    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);



    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glUseProgram(shaderProgram);

    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

   
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");

    float xPos = 0.0f;
    float yPos = 0.5f; 
    float speedX = -0.005f;
    float speedY = 0.005f;

    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);

        xPos += speedX;
        yPos += speedY;
        if (xPos > 1.0f || xPos < -1.0f)
            speedX *= -1.0f; 
        if (yPos > 1.0f || yPos < -1.0f)
            speedY *= -1.0f; 

        model = glm::translate(model, glm::vec3(xPos, yPos, 0.0f));

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
