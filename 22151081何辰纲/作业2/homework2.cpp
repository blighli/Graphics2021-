#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include <vector>
#include <stb_image.h>
#include "shader.h"
#include "Camera.h"
#define M_PI 3.14159265358979323846
#define WINW 600
#define WINH 600
#define PLNUM 4

//Camera
Camera camera(glm::vec3(0., 0., 10.));
float lastX = WINW / 2.;
float lastY = WINH / 2.;
bool firstMouse = true;
float deltaTime = 0.f;
float lastFrame = 0.f;

glm::vec3 lightPos(0., 7., 15.);

#pragma region opengl glad+glfw init
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
#pragma endregion

#pragma region shpere
glm::vec3 getPoint(GLfloat u, GLfloat v, GLfloat r) {
    GLfloat z = r * std::cos(M_PI * u), x = r * std::sin(M_PI * u) * std::cos(2 * M_PI * v), y = r * std::sin(M_PI * u) * std::sin(2 * M_PI * v);
    return glm::vec3(x, y, z);
}

std::vector<GLuint> ofst = { 0,0,0,1,1,1,0,0,1,1,1,0 };
void createSphere(GLfloat* shpere, GLuint Longitude, GLuint Latitude, GLfloat r) {
    // Longitude：经线切分个数
    // Latitude：纬线切分个数
    GLfloat lon_step = 1. / Longitude;
    GLfloat lat_step = 1. / Latitude;
    GLuint offset = 0;
    for (int lat = 0; lat < Latitude; lat++) {
        for (int lon = 0; lon < Longitude; lon++) {
            // 一次构造4个点，两个三角形，
            for (int i = 0; i < 6; i++) {
                auto la = (lat + ofst[2 * i]) * lat_step;
                auto lo = (lon + ofst[2 * i + 1]) * lon_step;
                glm::vec3 point = getPoint(lo, la, r);
                memcpy(shpere + offset, glm::value_ptr(point), 3 * sizeof(GLfloat));
                offset += 3;
                memcpy(shpere + offset, glm::value_ptr(glm::vec3(1.,1.,1.)), 3 * sizeof(GLfloat));
                offset += 3;
                shpere[offset++] = la;
                shpere[offset++] = lo;
                //memcpy(shpere + offset, glm::value_ptr(glm::vec3(std::cos(2 * M_PI * la) * std::sin(M_PI * lo), std::sin(2 * M_PI * la) * std::sin(M_PI * lo), std::cos(M_PI * lo))), 3 * sizeof(GLfloat));
                memcpy(shpere + offset, glm::value_ptr(point), 3 * sizeof(GLfloat));
                offset += 3;
            }
            /*
            glm::vec3 point1 = getPoint(lat * lat_step, lon * lon_step, r);
            glm::vec3 point2 = getPoint((lat + 1) * lat_step, lon * lon_step, r);
            glm::vec3 point3 = getPoint((lat + 1) * lat_step, (lon + 1) * lon_step, r);
            glm::vec3 point4 = getPoint(lat * lat_step, (lon + 1) * lon_step, r);
            memcpy(shpere + offset, glm::value_ptr(point1), 3 * sizeof(GLfloat));
            offset += 3;
            shpere[offset++] = lat * 1. / Latitude, shpere[offset++] = lon * 1. / Longitude;
            memcpy(shpere + offset, glm::value_ptr(point4), 3 * sizeof(GLfloat));
            offset += 3;
            shpere[offset++] = lat * 1. / Latitude, shpere[offset++] = (lon + 1) * 1. / Longitude;
            memcpy(shpere + offset, glm::value_ptr(point3), 3 * sizeof(GLfloat));
            offset += 3;
            shpere[offset++] = (lat + 1) * 1. / Latitude, shpere[offset++] = (lon + 1) * 1. / Longitude;
            memcpy(shpere + offset, glm::value_ptr(point1), 3 * sizeof(GLfloat));
            offset += 3;
            shpere[offset++] = lat * 1. / Latitude, shpere[offset++] = lon * 1. / Longitude;
            memcpy(shpere + offset, glm::value_ptr(point3), 3 * sizeof(GLfloat));
            offset += 3;
            shpere[offset++] = (lat + 1) * 1. / Latitude, shpere[offset++] = (lon + 1) * 1. / Longitude;
            memcpy(shpere + offset, glm::value_ptr(point2), 3 * sizeof(GLfloat));
            offset += 3;
            shpere[offset++] = (lat + 1) * 1. / Latitude, shpere[offset++] = lon * 1. / Longitude;
            */
        }
    }
}

glm::vec3 spherePosition[] = {
    glm::vec3(0.0,2.0,0.0),
    glm::vec3(7.2f,  1.0f, -5.0f),
    glm::vec3(-6.5f, -5.2f, 2.5f),
    glm::vec3(3.3f, -3.0f, 3.5f),
    glm::vec3(-8.3f,  1.0f, -3.5f)
};

glm::vec3 sphereSize[] = {
    glm::vec3(1.,1.,1.),
    glm::vec3(.4,.4,.4),
    glm::vec3(.7,.7,.7),
    glm::vec3(.6,.6,.6),
    glm::vec3(.4,.4,.4)
};

float sphereSpeed[] = { -.5,-.9,.4,.8,1. };

#pragma endregion
const GLuint lats = 60;
const GLuint lons = 30;

int main()
{
    GLfloat vertices[6 * 11 * lats * lons];
    //GLfloat uvs[6 * 2 * lats * lons];
    std::cout << "total: " << sizeof(vertices) << std::endl;
    createSphere(vertices, lats, lons, 1.);
    
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);   // 主版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);   // 副版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(WINW, WINH, "temp", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader ourShader("vs3.glsl", "fs3.glsl");
    Shader lightShader("vs2.glsl", "fs2.glsl");
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // normal attribute
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Add Light cube
    float vertices2[] = {
       -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
       -0.5f,  0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,

       -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,
       -0.5f, -0.5f,  0.5f,

       -0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,
       -0.5f, -0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

       -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
       -0.5f, -0.5f,  0.5f,
       -0.5f, -0.5f, -0.5f,

       -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f,  0.5f,
       -0.5f,  0.5f, -0.5f,
    };
    unsigned int LightVAO, LightVBO;
    glGenVertexArrays(1, &LightVAO);
    glGenBuffers(1, &LightVBO);
    glBindBuffer(GL_ARRAY_BUFFER, LightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glBindVertexArray(LightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //glGenBuffers(1,&)

    // load and create a texture 
    // -------------------------
    unsigned int textures[PLNUM];
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    for (int i = 0; i < PLNUM; i++) {
        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        std::string temp = std::to_string(i+1) + ".bmp";
        unsigned char* data = stbi_load(temp.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    ourShader.setInt("texture", 0);

    glm::mat4 model= glm::mat4(1.0f);
    model= glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    ourShader.setMat4("model", model);
    glm::mat4 view = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(3 * std::sin((float)glfwGetTime()), 0., -6 + 3 * std::cos((float)glfwGetTime())));
    view = glm::translate(view, glm::vec3(0., 0., -10.f));
    ourShader.setMat4("view", view);
    glm::mat4 projection= glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)WINW / WINH, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);
    std::vector<glm::mat4> mm(PLNUM, model);
    for (int i = 0; i < PLNUM; i++) {
        mm[i] = glm::scale(mm[i], sphereSize[i]);
        mm[i] = glm::translate(mm[i], spherePosition[i]);
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }

    lightShader.use();
    lightShader.setMat4("projection", projection);
    glm::mat4 lightModelMat = glm::mat4(1.f);
    lightModelMat = glm::translate(lightModelMat, lightPos);
    lightShader.setMat4("model", lightModelMat);

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        //glClearColor(1., .5, 0., 1.);
        glClearColor(.1, .1, 0.1, 1.);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //draw
        ourShader.use();
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("viewPos", camera.Position);
        ourShader.setVec3("lightPos", lightPos);
        //model = glm::rotate(model, glm::radians(-1.f), glm::vec3(0.0f, 0.0f, 1.0f));
        //ourShader.setMat4("model", model);
        view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        glBindVertexArray(VAO);
        for (int i = 0; i < PLNUM; i++) {
            ourShader.setInt("texture1", i);

            mm[i] = glm::rotate(mm[i], glm::radians(sphereSpeed[i]), glm::vec3(0.0f, 0.0f, 1.0f));
            ourShader.setMat4("model", mm[i]);
            //glDrawArrays(GL_TRIANGLES, 0, 6*lats*lons);
            glDrawArrays(GL_TRIANGLES, 0, 6 * lats * lons);
        }
        

        //Draw LightCube
        
        lightShader.use();
        lightShader.setMat4("view", view);
        glBindVertexArray(LightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &LightVAO);
    glDeleteBuffers(1, &LightVBO);

    glfwTerminate();
    return 0;
}