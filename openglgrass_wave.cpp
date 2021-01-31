
#include <glad/glad.h>
#include<glfw/glfw3.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader.h"

using namespace std;

float baseOut = 0.8f;
float baseOutmin = 0.5f;
float baseOuthigh = 1.0f;
float vertexsOut[] = {
	//left
	-baseOut, -baseOut, -(baseOut-baseOutmin), 1.0f, 1.0f,  //下
		baseOut, -baseOut, -(baseOut-baseOutmin), 0.0f, 1.0f, //下
		baseOut, baseOut, -(baseOut), 0.0f, 0.0f,
		baseOut, baseOut, -(baseOut), 0.0f, 0.0f,
		-baseOut, baseOut, -(baseOut), 1.0f, 0.0f,
		-baseOut, -baseOut, -(baseOut - baseOutmin), 1.0f, 1.0f, //下
		//right
			-baseOut, -baseOut, (baseOut-baseOutmin), 1.0f, 1.0f,
			baseOut, -baseOut, (baseOut-baseOutmin), 0.0f, 1.0f,
			baseOut, baseOut , (baseOut), 0.0f, 0.0f,
			baseOut, baseOut , (baseOut), 0.0f, 0.0f,
			-baseOut, baseOut , (baseOut), 1.0f, 0.0f,
			-baseOut, -baseOut , (baseOut-baseOutmin), 1.0f, 1.0f,

			//front 
				-(baseOut), baseOut, baseOut, 0.0f, 0.0f,
				-(baseOut), baseOut, -baseOut, 1.0f, 0.0f,
				-(baseOut-baseOutmin) , -baseOut, -baseOut, 1.0f, 1.0f,//下
				-(baseOut-baseOutmin) , -baseOut, -baseOut, 1.0f, 1.0f,//下
				-(baseOut-baseOutmin), -baseOut, baseOut, 0.0f, 1.0f,  //下
				-(baseOut), baseOut, baseOut, 0.0f, 0.0f,
				//behide
					(baseOut), baseOut, baseOut, 0.0f, 0.0f,
					(baseOut), baseOut, -baseOut, 1.0f, 0.0f,
					(baseOut-baseOutmin) , -baseOut, -baseOut, 1.0f, 1.0f,  //下
					(baseOut-baseOutmin) , -baseOut, -baseOut, 1.0f, 1.0f,  //下
					(baseOut-baseOutmin), -baseOut, baseOut, 0.0f, 1.0f,	//下
					(baseOut) , baseOut, baseOut, 0.0f, 0.0f, 

					//bottom  (left)
						-baseOut +0.5f, -baseOut, (baseOut-baseOutmin), 0.0f, 1.0f,
						-baseOut +0.5f, -baseOut, -(baseOut-baseOutmin), 0.0f, 0.0f,
						(baseOut-baseOutmin), -baseOut, -(baseOut-baseOutmin), 1.0f, 0.0f,
						(baseOut-baseOutmin), -baseOut, -(baseOut-baseOutmin), 1.0f, 0.0f,
						(baseOut-baseOutmin), -baseOut, (baseOut-baseOutmin), 1.0f, 1.0f,
						-(baseOut-baseOutmin), -baseOut, (baseOut-baseOutmin), 0.0f, 1.0f,
						
						/*
						//top
							-baseOut, baseOut + wave_y, baseOut + wave_z, 1.0f, 0.0f,
							-baseOut, baseOut + wave_y, -baseOut + wave_z, 1.0f, 1.0f,
							baseOut, baseOut + wave_y, -baseOut + wave_z, 0.0f, 1.0f,
							baseOut, baseOut + wave_y, -baseOut + wave_z, 0.0f, 1.0f,
							baseOut, baseOut + wave_y, baseOut + wave_z, 0.0f, 0.0f,
							-baseOut, baseOut + wave_y, baseOut + wave_z, 1.0f, 0.0f
						*/
};

float baseIn = 0.6f;
float baseInmin = 0.3f;
float baseInhigh = 1.0f;
float vertexsIn[] = {
	//left
	-baseIn, -baseIn, -(baseIn - baseInmin), 1.0f, 1.0f,  //下
		baseIn, -baseIn, -(baseIn - baseInmin), 0.0f, 1.0f,//下
		baseIn, baseIn + baseInhigh, -(baseIn - baseInmin), 0.0f, 0.0f,
		baseIn, baseIn + baseInhigh, -(baseIn - baseInmin), 0.0f, 0.0f,
		-baseIn, baseIn + baseInhigh, -(baseIn - baseInmin), 1.0f, 0.0f, 
		-baseIn, -baseIn, -(baseIn - baseInmin), 1.0f, 1.0f,  //下
		//right
			-baseIn, -baseIn, (baseIn - baseInmin), 1.0f, 1.0f,  //下
			baseIn, -baseIn, (baseIn - baseInmin), 0.0f, 1.0f,//下
			baseIn, baseIn + baseInhigh , (baseIn - baseInmin), 0.0f, 0.0f,
			baseIn, baseIn + baseInhigh , (baseIn - baseInmin), 0.0f, 0.0f,
			-baseIn, baseIn + baseInhigh , (baseIn - baseInmin), 1.0f, 0.0f,
			-baseIn, -baseIn , (baseIn - baseInmin), 1.0f, 1.0f,  //下

			//front 
				-baseIn + 0.5f, baseIn + baseInhigh, baseIn, 0.0f, 0.0f,
				-baseIn + 0.5f, baseIn + baseInhigh, -baseIn, 1.0f, 0.0f,
				-baseIn + 0.5f , -baseIn, -baseIn, 1.0f, 1.0f, //下
				-baseIn + 0.5f , -baseIn, -baseIn, 1.0f, 1.0f, //下
				-baseIn + 0.5f, -baseIn, baseIn, 0.0f, 1.0f,   //下
				-baseIn + 0.5f, baseIn + baseInhigh, baseIn, 0.0f, 0.0f,
				//behide
					(baseIn - baseInmin), baseIn + baseInhigh, baseIn, 0.0f, 0.0f,
					(baseIn - baseInmin), baseIn + baseInhigh, -baseIn, 1.0f, 0.0f,
					(baseIn - baseInmin) , -baseIn, -baseIn, 1.0f, 1.0f,  //下
					(baseIn - baseInmin) , -baseIn, -baseIn, 1.0f, 1.0f,  //下
					(baseIn - baseInmin), -baseIn, baseIn, 0.0f, 1.0f,    //下
					(baseIn - baseInmin) , baseIn + baseInhigh, baseIn, 0.0f, 0.0f,

					//bottom  (left)
						-baseIn + 0.5f , -baseIn, (baseIn - baseInmin), 0.0f, 1.0f,
						-baseIn + 0.5f, -baseIn, -(baseIn - baseInmin), 0.0f, 0.0f,
						(baseIn - baseInmin), -baseIn, -(baseIn - baseInmin), 1.0f, 0.0f,
						(baseIn - baseInmin), -baseIn, -(baseIn - baseInmin), 1.0f, 0.0f,
						(baseIn - baseInmin), -baseIn, (baseIn - baseInmin), 1.0f, 1.0f,
						-(baseIn - baseInmin), -baseIn, (baseIn - baseInmin), 0.0f, 1.0f,

						/*
						//top
							-baseIn, baseIn + wave_y, baseIn + wave_z, 1.0f, 0.0f,
							-baseIn, baseIn + wave_y, -baseIn + wave_z, 1.0f, 1.0f,
							baseIn, baseIn + wave_y, -baseIn + wave_z, 0.0f, 1.0f,
							baseIn, baseIn + wave_y, -baseIn + wave_z, 0.0f, 1.0f,
							baseIn, baseIn + wave_y, baseIn + wave_z, 0.0f, 0.0f,
							-baseIn, baseIn + wave_y, baseIn + wave_z, 1.0f, 0.0f
						*/
};


float planeVertices[] = {
	// positions          // texture Coords 
	 5.0f, -2.0f,  5.0f,  2.0f, 0.0f,
	-5.0f, -2.0f,  5.0f,  0.0f, 0.0f,
	-5.0f, -2.0f, -5.0f,  0.0f, 2.0f,

	 5.0f, -2.0f,  5.0f,  2.0f, 0.0f,
	-5.0f, -2.0f, -5.0f,  0.0f, 2.0f,
	 5.0f, -2.0f, -5.0f,  2.0f, 2.0f
};

float stoneVertices[] = {
	// positions          // texture Coords 

	 -2.0f, -2.0f, -3.0f,  0.0f, 1.0f,  //左上
	-2.0f, 2.0f,  -3.0f,  0.0f, 0.0f,  //左下
	 2.0f, 2.0f,  -3.0f,  1.0f, 0.0f,  //右下
	 2.0f, 2.0f,  -3.0f,  1.0f, 0.0f,  //右下
	 2.0f, -2.0f, -3.0f,  1.0f, 1.0f,  //右上
	-2.0f, -2.0f, -3.0f,  0.0f, 1.0f,  //左上
	
	 };

float flowerVertices[] = {

	-0.3f,-0.3f,0.0f,1.0f,1.0f,
	-0.3f,0.3f,0.0f,1.0f,0.0f,
	0.3f,0.3f,0.0f,0.0f,0.0f,
	0.3f,0.3f,0.0f,0.0f,0.0f,
	0.3f,-0.3f,0.0f,0.0f,1.0f,
	-0.3f,-0.3f,0.0f,1.0f,1.0f,

	0.0f,-0.3f,0.3f,1.0f,1.0f,
	0.0f,0.3f,0.3f,1.0f,0.0f,
	0.0f,0.3f,-0.3f,0.0f,0.0f,
	0.0f,0.3f,-0.3f,0.0f,0.0f,
	0.0f,-0.3f,-0.3f,0.0f,1.0f,
	0.0f,-0.3,0.3f,1.0f,1.0f

};

unsigned int indices[] = {
		0, 1, 2,  //第一个三角形
		0, 2, 3   //第二个三角形
};

glm::vec3 cubePosition[] = {
	   glm::vec3(0.0f, -0.2f, -0.8f),
	   glm::vec3(0.8f, -0.5f, 0.0f),
	   glm::vec3(-0.8f, -0.5f, 0.0f),
	   glm::vec3(-0.8f, 0.0f, 0.0f)
};

glm::vec3 flowerPosition[] = {
	//glm::vec3(-0.9f, -0.2f, 0.3f),
	glm::vec3(-0.7f, -0.2f, -0.9f),
	glm::vec3(0.7f, 0.0f, 0.3f),
	glm::vec3(0.5f, -0.5f, 0.7f)
};

int w = 800, h = 600;
unsigned int outVBO, outVAO, outEBO;
unsigned int inVBO, inVAO, inEBO;
unsigned int planeVBO, planeVAO, planeEBO;
unsigned int stoneVBO, stoneVAO, stoneEBO;
unsigned int flowerVBO, flowerVAO, flowerEBO;
unsigned int texture1;

GLFWwindow* init();
void VAOset();
unsigned int loadTexture(char const* path);
void changeArray(float* arrays, char pos, float value,float lastvalue);

int main() {


	GLFWwindow* window = init();

	//深度检测
	glEnable(GL_DEPTH_TEST);

	//处理图片
	unsigned int grassTexture = loadTexture("grass.png");
	unsigned int planeTexture = loadTexture("plane.png");
	unsigned int stoneTexture = loadTexture("stone.png");
	unsigned int flowerTexture = loadTexture("flower.png");
	Shader shader("wave.fs", "wave.vs");

	shader.use();
	shader.setInt("texture1", 0);


	float curTime = (float)(glfwGetTime());
	float lastTime = curTime;
	float wave_change_out = 0.0f;
	float last_wave_change_out = 0.0f;
	float wave_change_in = 0.0f;
	float last_wave_change_in = 0.0f;
	//渲染引擎(GLAD)
		//使窗口在绘制完后依然存在
	while (!glfwWindowShouldClose(window)) {

		//设置颜色
		glClearColor(0.7f, 0.8f, 0.9f, 1.0f);
		//应用颜色
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //同时清除上一帧深度缓存

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view;
		glm::mat4 projection;

		projection = glm::perspective(glm::radians(45.0f), float(w / h), 0.1f, 100.0f); //仰角，窗口比例，...，...
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		VAOset();
		
		//草地
		glBindVertexArray(planeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, planeTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, 2 * (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.5f, 0.0f));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		//石头
		glBindVertexArray(stoneVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, stoneTexture);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.3f, 0.3f, -0.2f));
		//model = glm::rotate(model, 2 * (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.5f, 0.0f));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//花
		for (unsigned int i = 0; i < 3; i++)
		{
			glBindVertexArray(flowerVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, flowerTexture);
			model = glm::mat4(1.0f);
			model = glm::translate(model, flowerPosition[i]);
			//model = glm::rotate(model, 2 * (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 0.4f*(i+1), 0.0f));
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 12);
		}

		//草丛
		float time = (float)glfwGetTime();
		curTime = (float)(glfwGetTime());
		wave_change_out = sin(curTime);
		last_wave_change_out = sin(lastTime);
		wave_change_in = sin(curTime + 1);
		last_wave_change_in = sin(lastTime + 1);

		//cout << curTime << " ";
		changeArray(vertexsOut, 'x', wave_change_out / 3.5, last_wave_change_out / 3.5);
		changeArray(vertexsOut, 'y', wave_change_out / 5.0, (last_wave_change_out / 5.0));
		changeArray(vertexsIn, 'x', wave_change_in / 4.0, last_wave_change_in / 4.0);

		lastTime = curTime;
	
		for (int i = 0; i < 3; i++) {

			VAOset();

			glBindVertexArray(outVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, grassTexture);
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePosition[i]);
			//model = glm::rotate(model, 2 * (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 30);

			glBindVertexArray(inVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, grassTexture);
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePosition[i]);
			//model = glm::rotate(model, 2 * (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 30);

		}
		
		//cout << endl;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//释放删除分配的所有资源，正确退出应用程序
	glfwTerminate();

	return 0;
}

GLFWwindow* init() {

	//初始化glfw
	glfwInit();
	//初始化window
	GLFWwindow* window = glfwCreateWindow(w, h, "test", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	//初始化glad ，用来管理指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return NULL;
	}
	//视口，OPENGL渲染窗口的尺寸大小，opengl可以根据窗口大小显示数据和坐标
	//当窗口大小调整时，视口也应该被调整。可以考虑使用一个回调函数framebuffer_size_callback。
	glViewport(0, 0, w, h);

	return window;
}

void VAOset() {

	glGenVertexArrays(1, &outVAO);
	glGenBuffers(1, &outVBO);
	glGenBuffers(1, &outEBO);
	glBindVertexArray(outVAO);

	glGenTextures(1, &texture1);//纹理

	//绑定
	glBindBuffer(GL_ARRAY_BUFFER, outVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, outEBO);
	
	//向显卡写入坐标值
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexsOut), vertexsOut, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//顶点位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//纹理位置
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &inVAO);
	glGenBuffers(1, &inVBO);
	glGenBuffers(1, &inEBO);
	glBindVertexArray(inVAO);
	glBindBuffer(GL_ARRAY_BUFFER, inVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, inEBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexsIn), vertexsIn, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glGenBuffers(1, &planeEBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &stoneVAO);
	glGenBuffers(1, &stoneVBO);
	glGenBuffers(1, &stoneEBO);
	glBindVertexArray(stoneVAO);
	glBindBuffer(GL_ARRAY_BUFFER, stoneVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, stoneEBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stoneVertices), stoneVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &flowerVAO);
	glGenBuffers(1, &flowerVBO);
	glGenBuffers(1, &flowerEBO);
	glBindVertexArray(flowerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, flowerVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flowerEBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(flowerVertices), flowerVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void changeArray(float * arrays,char pos,float value, float lastvalue) {

	//cout << arrays[10] << "  ";
	
	int posnum = 0;
	float mul = 0;
	switch (pos) {
	case 'x': posnum = 0; break;
	case 'y':posnum = 1;  break;
	case 'z':posnum = 2;  break;
	};

	for (int i = 10; i < 5 * 6 * 5; i++) {
		if (i < 5 * 6 * 2) {
			if (i % 30 == 10+posnum || i % 30 == 15 + posnum || i % 30 == 20 + posnum) {
				arrays[i] = arrays[i] - lastvalue + value;
			}
		}
		else if (i < 5 * 6 * 4) {
			if (i % 30 == 0 + posnum || i % 30 == 5 + posnum || i % 30 == 25 + posnum) {
				arrays[i] = arrays[i] - lastvalue + value;
			}
		}
	}
	//cout << vertexs[10] << "  ";
	//cout << endl;

}