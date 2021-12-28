#include<iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Shader.h"
#include "Camera.h"
using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

unsigned int EBO;
unsigned int VBO;
unsigned int VAO;
glm::vec3 Positions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
};
float seg = 50;


void GetSphere() {
	// 获得球的各个顶点的坐标并绑定VAO、VBO和EBO
	std::vector<float> points;
	std::vector<int>indices;

	float PI = std::acos(-1);
	for (int i = 0; i <= seg; i++)
	{
		for (int j = 0; j <= seg; j++) {
			float xse = j / seg;
			float yse = i / seg;
			float x = std::cos(xse * 2.0f * PI) * std::sin(yse * PI);
			float y = std::cos(yse * PI);
			float z = std::sin(xse * 2.0f * PI) * std::sin(yse * PI);
			points.push_back(x);
			points.push_back(y);
			points.push_back(z);
			points.push_back(xse * 1.0f);
			points.push_back(yse * 1.0f);
		}
	}
	for (int i = 0; i < seg; i++)
	{
		for (int j = 0; j < seg; j++)
		{
			indices.push_back(i * ((int)seg + 1) + j);
			indices.push_back((i + 1) * ((int)seg + 1) + j);
			indices.push_back((i + 1) * ((int)seg + 1) + j + 1);
			indices.push_back(i * ((int)seg + 1) + j);
			indices.push_back((i + 1) * ((int)seg + 1) + j + 1);
			indices.push_back(i * ((int)seg + 1) + j + 1);
		}
	}

	
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void LoadTexture(unsigned int& texture, const string& path) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
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

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f, 0.0f, 0.0f),	// 太阳位置
  glm::vec3(4.0f, 0.0f, 0.0f),
  glm::vec3(5.0f, 0.0f, 0.0f)
};

int main(int argc, char** argv[])
{
	glfwInit();
	glEnable(GL_DEPTH_TEST);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Project2", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, 800, 600);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	GLenum err = glewInit();

	glm::vec3 lightPos(0.0f, 0.0f, 0.0f);	// 光源位置，与太阳重合
	// 创建Shader
	Shader sunshader("Shaders/sun.vs", "Shaders/sun.fs");
	Shader earthshader("Shaders/earth.vs", "Shaders/earth.fs");
	Shader moonShader("Shaders/moon.vs", "Shaders/moon.fs");
	
	
	// 初始化顶点
	GetSphere();

	// 加载贴图
	unsigned int texture_sun, texture_earth, texture_moon;
	LoadTexture(texture_sun, "Textures/Sun.jpg");
	LoadTexture(texture_earth, "Textures/Earth.jpg");
	LoadTexture(texture_moon, "Textures/Moon.png");

	
	int selfSpeed = 1;
	int earthSpeed = 4;
	int sunSpeed = 2;
	float angle = 20.0f;

	// 主循环
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		// Porjection Matrix
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		// View Matrix
		glm::mat4 view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);

		//模型矩阵
		for (unsigned int i = 0; i < 3; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			//太阳
			if (i == 0) {
				sunshader.use();
				sunshader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
				sunshader.setVec3("lightPos", lightPos[0], lightPos[1], lightPos[2]);
				sunshader.setMat4("view", view);
				sunshader.setMat4("projection", projection);
				glBindVertexArray(VAO);
				model = glm::rotate(model, glm::radians(angle) + currentFrame * selfSpeed, glm::vec3(0.0f, 1.0f, 0.0f));//自转
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture_sun);
				sunshader.setMat4("model", model);
			}

			//地球
			if (i == 1) {
				earthshader.use();
				earthshader.setVec3("lightPos", lightPos[0], lightPos[1], lightPos[2]);
				earthshader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
				earthshader.setMat4("view", view);
				earthshader.setMat4("projection", projection);
				glBindVertexArray(VAO);
				
				model = glm::rotate(model, glm::radians(angle) + currentFrame * sunSpeed, glm::vec3(0.0f, 1.0f, 0.0f));//绕太阳公转
				model = glm::translate(model, cubePositions[i]);                                                        //定位
				model = glm::rotate(model, glm::radians(angle) + currentFrame * selfSpeed, glm::vec3(0.0f, 1.0f, 0.0f));//自转
				model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));                                                 //缩放

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture_earth);

				earthshader.setMat4("model", model);
			}
			//月亮
			if (i == 2) {
				moonShader.use();
				moonShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
				moonShader.setVec3("lightPos", lightPos[0], lightPos[1], lightPos[2]);
				moonShader.setMat4("view", view);
				moonShader.setMat4("projection", projection);
				glBindVertexArray(VAO);
				model = glm::translate(model, cubePositions[0]);
				model = glm::rotate(model, glm::radians(angle) + currentFrame * sunSpeed, glm::vec3(0.0f, 1.0f, 0.0f)); //绕太阳公转
				model = glm::translate(model, -cubePositions[0]);

				model = glm::translate(model, cubePositions[1]);                                                         //公转坐标-地球
				model = glm::rotate(model, glm::radians(angle) + currentFrame * earthSpeed, glm::vec3(0.0f, 1.0f, 0.0f));//绕地球公转
				model = glm::translate(model, -cubePositions[1]);

				model = glm::translate(model, cubePositions[i]);                                                        //定位


				model = glm::rotate(model, glm::radians(angle) + currentFrame * selfSpeed, glm::vec3(0.0f, 1.0f, 0.0f));//自转
				model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));                                                 //缩放

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture_moon);
				moonShader.setMat4("model", model);
			}
			glDrawElements(GL_TRIANGLES, (int)(seg * seg) * 6, GL_UNSIGNED_INT, 0);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}


