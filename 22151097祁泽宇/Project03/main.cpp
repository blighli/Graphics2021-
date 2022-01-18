#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "Mesh.h"
#include "Model.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//发光正方体的数据
#pragma region Model Data

float vertices[] = {
	//position             //normal             //TexCoord 
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,	0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,	0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,	1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,	0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,	0.0f, 1.0f,

};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

#pragma region Camera Declare
//建立camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera(cameraPos, cameraTarget, cameraUp);
#pragma endregion

#pragma region Light Declare
//position angle color
LightDirectional lightD(
	glm::vec3(135.0f, 0, 0),
	glm::vec3(0.5f, 0.5f, 0.5f));

LightPoint lightP0(glm::vec3(1.0f, 0, 0),
	glm::vec3(1.0f, 0, 0));

LightPoint lightP1(glm::vec3(0, 1.0f, 0),
	glm::vec3(0, 1.0f, 0));

LightPoint lightP2(glm::vec3(0, 0, 1.0f),
	glm::vec3(0, 0, 1.0f));

LightPoint lightP3(glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(1.0f, 0, 1.0f));

LightSpot lightS(glm::vec3(0, 8.0f, 0.0f),
	glm::vec3(135.0f, 0, 0),
	glm::vec3(0, 0, 1.5f));
#pragma endregion

#pragma region Input Declare
//移动用
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

void processInput(GLFWwindow* window) {
	//看是不是按下esc键 然后退出
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	//更流畅点的摄像机系统
	if (deltaTime != 0) {
		camera.cameraPosSpeed = 5 * deltaTime;
	}
	//camera前后左右根据镜头方向移动
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.PosUpdateForward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.PosUpdateBackward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.PosUpdateLeft();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.PosUpdateRight();
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.PosUpdateUp();
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.PosUpdateDown();


}
float lastX;
float lastY;
bool firstMouse = true;

//鼠标控制镜头方向
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse == true)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float deltaX, deltaY;
	float sensitivity = 0.05f;

	deltaX = (xpos - lastX) * sensitivity;
	deltaY = (ypos - lastY) * sensitivity;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(deltaX, deltaY);

};
//缩放
float fov = 45.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

#pragma endregion 

unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format) {
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	// 加载并生成纹理
	int width, height, nrChannel;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture");
	}
	stbi_image_free(data);
	return TexBuffer;
}


int main(int argc, char* argv[]) {
	std::string exePath = argv[0];

#pragma region Open a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "3DHW", NULL, NULL);
	if (window == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//关闭鼠标显示
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//回调函数监听鼠标
	glfwSetCursorPosCallback(window, mouse_callback);
	//回调函数监听滚轮
	glfwSetScrollCallback(window, scroll_callback);

	//Init GLEW
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);

#pragma endregion

#pragma region Init Shader Program
	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
#pragma endregion

#pragma region Init Material
	Material* myMaterial = new Material(myShader,
		LoadImageToGPU("container2.png", GL_RGBA, GL_RGBA),
		LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA),
		LoadImageToGPU("matrix.jpg", GL_RGB, GL_RGB),
		glm::vec3(1.0f, 1.0f, 1.0f),
		150.0f);

#pragma endregion

#pragma region Init and Load Models to VAO,VBO
	Mesh cube(vertices);
	Model model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\nanosuit.obj");

#pragma endregion

#pragma region Init and Load Textures
	//坐标翻转
	stbi_set_flip_vertically_on_load(true);

#pragma endregion

#pragma region Prepare MVP matrices
	//model
	glm::mat4 modelMat;
	//view
	glm::mat4 viewMat;
	//projection
	glm::mat4 projMat;
#pragma endregion


	while (!glfwWindowShouldClose(window))
	{
		//Process Input
		processInput(window);

		//Clear Screen
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		//方块  10代表模型
		for (unsigned int i = 0; i < 11; i++)
		{
			if (i != 10) {
				//Set Model matrix
				modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
				float angle = 20.0f * (i);
				//float angle = 20.0f * i + 50*glfwGetTime();

				modelMat = glm::rotate(modelMat, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			}
			else {
				modelMat = glm::translate(glm::mat4(1.0f), { 0,-10,-5 });
			}

			//Set view matrix
			viewMat = camera.GetViewMatrix();

			//Set projection matrix
			projMat = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);


			//Set Material -> Shader Program
			myShader->use();

			//Set Material -> Uniforms
#pragma region Uniform
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

			glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			glUniform1f(glGetUniformLocation(myShader->ID, "time"), glfwGetTime());

			glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.color"), lightD.color.x, lightD.color.y, lightD.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.dirToLight"), lightD.direction.x, lightD.direction.y, lightD.direction.z);


			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.pos"), lightP0.position.x, lightP0.position.y, lightP0.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.color"), lightP0.color.x, lightP0.color.y, lightP0.color.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.quadratic"), lightP0.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.pos"), lightP1.position.x, lightP1.position.y, lightP1.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.quadratic"), lightP1.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.pos"), lightP2.position.x, lightP2.position.y, lightP2.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.quadratic"), lightP2.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.pos"), lightP3.position.x, lightP3.position.y, lightP3.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.quadratic"), lightP3.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.pos"), lightS.position.x, lightS.position.y, lightS.position.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.color"), lightS.color.x, lightS.color.y, lightS.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.quadratic"), lightS.quadratic);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOuter"), lightS.cosPhyOuter);
#pragma endregion


			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);


			if (i == 10) {
				model.Draw(myShader);
			}
			else {
				cube.DrawArray(myMaterial->shader, myMaterial->diffuse, myMaterial->specular, myMaterial->emission);
			}

		}

		//Clean up prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();

		//Recording the time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
	//Exit program
	glfwTerminate();
	return 0;

}

