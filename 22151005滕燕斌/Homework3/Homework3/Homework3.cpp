// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL/SOIL.h>

// 窗口尺寸
GLuint screenWidth = 800, screenHeight = 600;
GLFWwindow* window;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouseButton_callback(GLFWwindow* window, int button, int action, int mods);
void Do_Movement();

// 相机的参数
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// 光标位置
float lastX = (float)screenWidth / 2.0f;
float lastY = (float)screenHeight / 2.0f;
bool isControl = false; // 判断是否控制模型的旋转

// 用于控制模型
GLfloat Angle_X = 0, Angle_Y = 0, Scale = 0.2; // Angle用于旋转, Scale用于控制模型的缩放
glm::vec3 Axis_X(1.f, 0.f, 0.f);
glm::vec3 Axis_Y(0.f, 1.f, 0.f);

// 定义光源所在位置
glm::vec3 pointLightPositions[] = {
    glm::vec3(2.3f, -1.6f, -3.0f),
    glm::vec3(-1.7f, 0.9f, 1.0f)
};

void Init()
{
    // 初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    // 设置回调函数
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouseButton_callback);

    // Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 初始化glew
    glewExperimental = GL_TRUE;
    glewInit();

    // 
    glViewport(0, 0, screenWidth, screenHeight);

    // 开启深度测试
    glEnable(GL_DEPTH_TEST);
}

int main()
{
    // 初始化glfw和glew
    Init();

    // 创建并编译着色器
    Shader shader("model_loading.vs", "model_loading.frag");

    // 加载模型
    Model ourModel("nanosuit/nanosuit.obj");

    while (!glfwWindowShouldClose(window))
    {
        // 得到每一帧所在时间
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //
        glfwPollEvents();
        Do_Movement();

        // 清空颜色缓存
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        // 设置projection和view矩阵
        glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // 设置光源
        glUniform3f(glGetUniformLocation(shader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        // 光源 1
        glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(shader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shader.Program, "pointLights[0].linear"), 0.009);
        glUniform1f(glGetUniformLocation(shader.Program, "pointLights[0].quadratic"), 0.0032);
        // 光源 2 
        glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(shader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(shader.Program, "pointLights[1].linear"), 0.009);
        glUniform1f(glGetUniformLocation(shader.Program, "pointLights[1].quadratic"), 0.0032);

        // 设置model矩阵
        glm::mat4 model(1.f);
        model = glm::rotate(model, glm::radians((GLfloat)Angle_X), Axis_X);
        model = glm::rotate(model, glm::radians((GLfloat)Angle_Y), Axis_Y);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
        model = glm::scale(model, glm::vec3(Scale, Scale, Scale));	// It's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // 绘制
        ourModel.Draw(shader);

        glfwSwapBuffers(window);
    }

    // 释放资源
    glfwTerminate();
    return 0;
}

#pragma region "User input"

void Do_Movement()
{
    if (keys[GLFW_KEY_LEFT_SHIFT]) {
        // Camera controls
        if (keys[GLFW_KEY_W])
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (keys[GLFW_KEY_S])
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (keys[GLFW_KEY_A])
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (keys[GLFW_KEY_D])
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    if (isControl) {
        Angle_Y += xoffset * 0.07;
        Angle_X -= yoffset * 0.07;
    }
    else if(keys[GLFW_KEY_LEFT_SHIFT]){
        camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset < 0) {
        Scale /= 1.2;
        if (Scale <= 0.01) Scale = 0.01;
    }
    else {
        Scale *= 1.2;
        if (Scale >= 10) Scale = 10;
    }
    
}

void mouseButton_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
        switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:

            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:

            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            isControl = true;
            break;
        default:
            return;
        }
    else {
        isControl = false;
    }

}

#pragma endregion