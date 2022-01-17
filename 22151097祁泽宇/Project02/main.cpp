#include <iostream>
#include <algorithm>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//simple constant
//*******************************************************
constexpr unsigned int HEIGHT = 800;
constexpr unsigned int WIDTH = 600;
constexpr double MY_PI = 3.141592653589793116;
constexpr int hexSkyColor = 0x0f2350; 
constexpr float skyB = (0x0f2350 >> 0 ) % 256 / 255.f;
constexpr float skyG = (0x0f2350 >> 8 ) % 256 / 255.f;
constexpr float skyR = (0x0f2350 >> 16) % 256 / 255.f;
//*******************************************************
/*
 * constexpr glm::vec3 skyColor(0);
 * constexpr float skyR = skyColor.x;
 * constexpr float skyG = skyColor.y;
 * constexpr float skyB = skyColor.z;
*/
//*******************************************************

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;  
bool firstMouse = true;
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

//callback and processor
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    
}

//generate Sphere points
void initSphere(std::vector <float> &sphereVertices, std::vector <unsigned int> & sphereIndices, unsigned int xSegments, unsigned int ySegments, float radius = 1) {
    sphereIndices.clear();
    sphereVertices.clear();
    for (int y = 0; y <= ySegments; ++y) {
        for (int x = 0; x <= xSegments; ++x) {
            float xSegment = (float)x / xSegments;
            float ySegment = (float)y / ySegments;
            float xPos = radius * std::cos(xSegment * 2.0f * MY_PI) * std::sin(ySegment * MY_PI);
            float yPos = radius * std::cos(ySegment * MY_PI);
            float zPos = radius * std::sin(xSegment * 2.0f * MY_PI) * std::sin(ySegment * MY_PI);
            sphereVertices.push_back(xPos);
            sphereVertices.push_back(yPos);
            sphereVertices.push_back(zPos);

            sphereVertices.push_back(xSegment);
            sphereVertices.push_back(ySegment); // TEXTURE
        }
    }
    for (int i = 0; i < ySegments; i++)
    {
        for (int j = 0; j < xSegments; j++)
        {
            sphereIndices.push_back(i * (xSegments + 1) + j);
            sphereIndices.push_back((i + 1) * (xSegments + 1) + j);
            sphereIndices.push_back((i + 1) * (xSegments + 1) + j + 1);
            sphereIndices.push_back(i * (xSegments + 1) + j);
            sphereIndices.push_back((i + 1) * (xSegments + 1) + j + 1);
            sphereIndices.push_back(i * (xSegments + 1) + j + 1);
        }
    }
}
int main(int argCount, char *args[]) {
    //init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    //init Window
    GLFWwindow* window = glfwCreateWindow(HEIGHT, WIDTH, "test", NULL, NULL);
    if (!window) exit(1);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) exit(1);


    // init planet
    enum {
        MOON = 0,
        EARTH,
        SUN
    };
    glm::vec3 planetPositionsOld[] = {
        glm::vec3(9.0f, 0.0f,  0.0f), // moon
        glm::vec3(7.0f, 0.0f, 0.0f), //earth
        glm::vec3(0.0f, 0.0f, 0.0f)   //sun
    }; 
    glm::vec3 planetPositionsNew[] = {
        glm::vec3(9.0f, 0.0f,  0.0f), // moon
        glm::vec3(7.0f, 0.0f, 0.0f), //earth
        glm::vec3(0.0f, 0.0f, 0.0f)   //sun
    };
    const float planetRadius[] = {
        0.3, // moon
        0.9, // earth
        1.8  // sun
    };
    std::vector<float> vertexList; 
    vertexList.reserve(100000U);
    std::vector<unsigned int> indexList;
    indexList.reserve(100000U);
    initSphere(vertexList, indexList, 50, 50);

    // buffer data to GPU
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexList.size(), &(vertexList[0]), GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indexList.size(), &(indexList[0]), GL_STATIC_DRAW);

    /********************************************/
    int nrChannels;
    int sunWidth, sunHeight;
    unsigned char* sunTexture = stbi_load("sun.jpg", &sunWidth, &sunHeight, &nrChannels, 0);

	GLuint sunTextureID;
	glGenTextures(1, &sunTextureID);
	glBindTexture(GL_TEXTURE_2D, sunTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sunWidth, sunHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, sunTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(sunTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, sunTextureID);
    //**********************************************


    int moonWidth, moonHeight;
    unsigned char* moonTexture = stbi_load("moon.jpg", &moonWidth, &moonHeight, &nrChannels, 0);

    GLuint moonTextureID;
    glGenTextures(1, &moonTextureID);
    glBindTexture(GL_TEXTURE_2D, moonTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, moonWidth, moonHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, moonTexture);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(moonTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, moonTextureID);



    int earthWidth, earthHeight;
    unsigned char* earthTexture = stbi_load("earth.jpg", &earthWidth, &earthHeight, &nrChannels, 0);

    GLuint earthTextureID;
    glGenTextures(1, &earthTextureID);
    glBindTexture(GL_TEXTURE_2D, earthTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, earthWidth, earthHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, earthTexture);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(earthTexture);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, earthTextureID);


    //OpenGL config
    glClearColor(skyR, skyG, skyB, 1.0f);
    glClearDepth(1.f);
    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader sunShady("SunVertexShader", "SunFragmentShader"); // a simple sun shady
    Shader shady("PlanetVertexShader", "PlanetFragmentShader"); // a simple planet Shady

    while (!glfwWindowShouldClose(window))
    {

        // Time Recorder
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // clear Buffer
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        // set projection and view Matrix
        sunShady.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        sunShady.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        sunShady.setMat4("view", view);
        glBindVertexArray(VAO);

        // amplitude of variation
        float deltaAngle = 20.0f * deltaTime;
        float angle = 20.0f * currentFrame;
        //SUN
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, planetPositionsOld[SUN]);
        model = glm::rotate(model, glm::radians(5 * angle), glm::vec3(0.1f, 1.0f, 0.1f)); // Rotation
        planetPositionsNew[SUN] = model * glm::vec4(0, 0, 0, 1);
        sunShady.setInt("texture_", 0);
        sunShady.setMat4("model", model);
        sunShady.setFloat("radius", planetRadius[SUN]);
       // sunShady.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f));
        glDrawElements(GL_TRIANGLES, vertexList.size() * 3, GL_UNSIGNED_INT, 0);

        // set projection, view Matrix and sunPos
        shady.use();
        shady.setMat4("view", view);
        shady.setMat4("projection", projection);
        shady.setVec3("sunPos", planetPositionsNew[SUN]);

        //EARTH
        model = glm::mat4(1.0f);
        model = glm::translate(model, planetPositionsOld[SUN]);
        model = glm::rotate(model, glm::radians(deltaAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // Orbital revolution
        model = glm::translate(model, planetPositionsOld[EARTH] - planetPositionsOld[SUN]); 
        model = glm::rotate(model, glm::radians(5 * angle), glm::vec3(0.1f, 1.0f, 0.1f)); // Rotation
        planetPositionsNew[EARTH] = model * glm::vec4(0, 0, 0, 1);
        shady.setMat4("model", model);
        shady.setInt("texture_", 2);
        shady.setFloat("radius", planetRadius[EARTH]);
       // shady.setVec3("color", glm::vec3(0.0f, 0.0f, 1.0f));
        glDrawElements(GL_TRIANGLES, vertexList.size() * 3, GL_UNSIGNED_INT, 0);

        //MOON
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(deltaAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // relative angular velocity
        model = glm::translate(model, planetPositionsOld[EARTH]);
        model = glm::rotate(model, glm::radians(deltaAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // Orbital revolution
        model = glm::translate(model, planetPositionsOld[MOON] - planetPositionsOld[EARTH]);
        model = glm::rotate(model, glm::radians(5  * angle), glm::vec3(0.1f, 1.0f, 0.1f)); // Rotation
        planetPositionsNew[MOON] = model * glm::vec4(0, 0, 0, 1);
        shady.setMat4("model", model);
        shady.setInt("texture_", 1);
        shady.setFloat("radius", planetRadius[MOON]);
        //shady.setVec3("color", glm::vec3(0.0f, 1.0f, 0.0f));
        glDrawElements(GL_TRIANGLES, vertexList.size() * 3, GL_UNSIGNED_INT, 0);
        
        //update
        std::copy_n(planetPositionsNew, 3, planetPositionsOld); 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}