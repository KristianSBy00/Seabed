//------- Ignore this ----------
#include<filesystem>
namespace fs = std::filesystem;
//------------------------------

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <cmath>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"Fish.h"
#include"boidsController.h"

# define PI           3.14159265358979323846  /* pi */


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.1f, 0.0f,  0.1f,     1.0f, 1.0f, 1.0f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.1f, 0.0f, -0.1f,     1.0f, 1.0f, 1.0f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.1f, 0.0f, -0.1f,     1.0f, 1.0f, 1.0f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.1f, 0.0f,  0.1f,     1.0f, 1.0f, 1.0f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.1f, 0.0f,  0.1f,     1.0f, 1.0f, 1.0f,  	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.1f, 0.0f, -0.1f,     1.0f, 1.0f, 1.0f, 	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.5f,  0.0f,     1.0f, 1.0f, 1.0f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.1f, 0.0f, -0.1f,     1.0f, 1.0f, 1.0f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.1f, 0.0f, -0.1f,     1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.5f,  0.0f,     1.0f, 1.0f, 1.0f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.1f, 0.0f, -0.1f,     1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.1f, 0.0f,  0.1f,     1.0f, 1.0f, 1.0f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.5f,  0.0f,     1.0f, 1.0f, 1.0f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.1f, 0.0f,  0.1f,     1.0f, 1.0f, 1.0f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.1f, 0.0f,  0.1f,     1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.5f,  0.0f,     1.0f, 1.0f, 1.0f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};



// Vertices coordinates
GLfloat vertices_floor[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-20.0f, -1.0f,  20.0f,		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-20.0f, -1.0f, -20.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 20.0f, -1.0f, -20.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 20.0f, -1.0f,  20.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices_floor[] =
{
	0, 1, 2,
	0, 2, 3
};


// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f + 10.f,  0.1f,
	-0.1f, -0.1f + 10.f, -0.1f,
	 0.1f, -0.1f + 10.f, -0.1f,
	 0.1f, -0.1f + 10.f,  0.1f,
	-0.1f,  0.1f + 10.f,  0.1f,
	-0.1f,  0.1f + 10.f, -0.1f,
	 0.1f,  0.1f + 10.f, -0.1f,
	 0.1f,  0.1f + 10.f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

const unsigned int width = 1000;
const unsigned int height = 800;

int numBoids = 200;
Fish fish_list[3][200];

void draw_fish(Shader fish_shader){
	glm::mat4 model;

	float r = 0;
	float g = 0;
	float b = 0;


	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			r = 1;
			g = 0;
			b = 0;
		}
		else if (i == 1) {
			r = 0;
			g = 0;
			b = 1;
		}
		else {
			r = 0;
			g = 1;
			b = 0;
		}

		for (int j = 0; j < numBoids; j++) {
			model = fish_list[i][j].get_model_mat();

			glUniform3f(glGetUniformLocation(fish_shader.ID, "fishColor"), r, g, b);
			glUniformMatrix4fv(glGetUniformLocation(fish_shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}
	}
}


int main()
{
	//initBoids();
	BoidsController boidsController = BoidsController();
	boidsController.initBoids(0, PI / 2, PI / 2, numBoids, fish_list);
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Seabed", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);


	Shader floorShader("floor.vert", "floor.frag");
	// New
	VAO VAO2;
	VAO2.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO2(vertices_floor, sizeof(vertices_floor));
	// Generates Element Buffer Object and links it to indices
	EBO EBO2(indices_floor, sizeof(indices_floor));


	// Links VBO attributes such as coordinates and colors to VAO
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();



	//end of new
	// Generates Shader object using shaders default.vert and default.frag
	// Generates Vertex Array Object and binds it


	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));



	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 100.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	glm::vec3 floorPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 floorModel = glm::mat4(1.0f);
	floorModel = glm::translate(floorModel, floorPos);



	floorShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(floorShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(floorModel));
	glUniform4f(glGetUniformLocation(floorShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(floorShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/

	// Texture
	Texture floortex("sand.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	floortex.texUnit(floorShader, "tex0", 0);

	// Texture
	Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);

	// Original code from the tutorial


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.15f, 0.69f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 2000.0f);


		// Tells OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Exports the camera Position to the Fragment Shader for specular lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Export the camMatrix to the Vertex Shader of the pyramid
		camera.Matrix(shaderProgram, "camMatrix");

		//double x = sin(glfwGetTime() / 2) * 2;
		//double z = -cos(glfwGetTime() / 2) * 2;
		//double y = 0.5*sin(glfwGetTime()*2) + .5;

		//double hor_angle = CalcHeadingRad(delta_x, delta_z, delta_y);
		//double pitch = CalcPitchRad(delta_x, delta_z, delta_y);

		//glm::mat4 translation = glm::translate(glm::vec3(x, y, z));
		//glm::mat4 rot = get_rotation_vec(0, PI / 2, PI / 2, delta_x, delta_y, delta_z);

		//glm::mat4 model = translation * rot;

		//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		// Binds texture so that is appears in rendering
		brickTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();


		boidsController.update(numBoids, fish_list);
		draw_fish(shaderProgram);

		// Draw primitives, number of indices, datatype of indices, index of indices
		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		floorShader.Activate();
		glUniform3f(glGetUniformLocation(floorShader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Export the camMatrix to the Vertex Shader of the pyramid
		camera.Matrix(floorShader, "camMatrix");
		glm::mat4 model = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(floorShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		floortex.Bind();
		VAO2.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices_floor) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}