#include"Mesh.h"
#include"boidsController.h"
#include "obj.h"

# define PI           3.14159265358979323846  /* pi */

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>
#include "tiny_obj_loader.h"
#include <cstdio>
#include <stdio.h>


using namespace std;

const unsigned int width = 1366;
const unsigned int height = 768;

std::vector <Shoal> sholes;

Vertex vertices_triangle[] =
{ //     COORDINATES						/        COLORS          /    TexCoord   /        NORMALS       //
		Vertex{glm::vec3(-0.1f, 0.0f, 0.1f),	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Bottom side
		Vertex{glm::vec3(-0.1f, 0.0f, -0.1f),	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 5.0f)}, // Bottom side
		Vertex{glm::vec3(0.1f, 0.0f, -0.1f),	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 5.0f)}, // Bottom side
		Vertex{glm::vec3(0.1f, 0.0f, 0.1f),		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 0.0f)}, // Bottom side

		Vertex{glm::vec3(-0.1f, 0.0f, 0.1f),	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.8f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Left Side
		Vertex{glm::vec3(-0.1f, 0.0f, -0.1f),	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.8f, 0.5f, 0.0f), glm::vec2(5.0f, 0.0f)}, // Left Side
		Vertex{glm::vec3(0.0f, 0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.8f, 0.5f, 0.0f), glm::vec2(2.5f, 5.0f)}, // Left Side

		Vertex{glm::vec3(-0.1f, 0.0f, -0.1f),	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(5.0f, 0.0f)}, // Non-facing side
		Vertex{glm::vec3(0.1f, 0.0f, -0.1f),	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(0.0f, 0.0f)}, // Non-facing side
		Vertex{glm::vec3(0.0f, 0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(2.5f, 5.0f)}, // Non-facing side

		Vertex{glm::vec3(0.1f, 0.0f, -0.1f),	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.8f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f)}, // Right side
		Vertex{glm::vec3(0.1f, 0.0f, 0.1f),		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.8f, 0.5f, 0.0f), glm::vec2(5.0f, 0.0f)}, // Right side
		Vertex{glm::vec3(0.0f, 0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.8f, 0.5f, 0.0f), glm::vec2(2.5f, 5.0f)}, // Right side

		Vertex{glm::vec3(0.1f, 0.0f, 0.1f),		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.5f, 0.8f), glm::vec2(5.0f, 0.0f)}, // Facing side
		Vertex{glm::vec3(-0.1f, 0.0f, 0.1f),	glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.5f, 0.8f), glm::vec2(0.0f, 0.0f)}, // Facing side
		Vertex{glm::vec3(0.0f, 0.5f, 0.0f),		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.5f, 0.8f), glm::vec2(2.5f, 5.0f)}  // Facing side
};

GLuint indices_triangle[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};


// Vertices coordinates
Vertex vertices_floor[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-20.0f, -0.2f,  20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-20.0f, -0.2f, -20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(20.0f, -0.2f, -20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(20.0f, -0.2f,  20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
	Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
	Vertex{glm::vec3(1.0f, -1.0f,  1.0f)},
	Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
	Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
	Vertex{glm::vec3(1.0f,  1.0f, -1.0f)},
	Vertex{glm::vec3(1.0f,  1.0f,  1.0f)}
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


void print_ind(std::vector<GLuint>& print_ind_var) {
	for (int i = 0; i < print_ind_var.size(); i++) {
		printf("%d, ", print_ind_var[i]);
	}
	printf("\n");
}

void print_ver(std::vector<Vertex>& print_ver) {
	for (int i = 0; i < print_ver.size(); i++) {
		printf("%f %f, %f | %f %f, %f | %f %f, %f | %f, %f\n", 
			print_ver[i].position.x, print_ver[i].position.y, print_ver[i].position.z,
			print_ver[i].normal.x, print_ver[i].normal.y, print_ver[i].normal.z,
			print_ver[i].color.x, print_ver[i].color.y, print_ver[i].color.z,
			print_ver[i].texUV.x, print_ver[i].texUV.y
		);
	}
	printf("\n");
}


void print_vec3_list(std::vector<glm::vec3>& guy_to_print) {
	for (int i = 0; i < guy_to_print.size(); i++) {
		printf("<%f, %f, %f>\n", guy_to_print[i].x, guy_to_print[i].y, guy_to_print[i].z);
	}
}


void draw_fish(Mesh fishMesh, Shader fishShader, Camera camera, glm::vec3 lightPos, std::vector<Shoal>& sholes_in) {
	glm::mat4 model;

	for (int i = 0; i < sholes_in.size(); i++) {

		std::vector<Fish>& shole = sholes_in[i].get();

		glm::vec3 color = sholes_in[i].color;

		for (int j = 0; j < shole.size(); j++) {

			Fish& fish = shole[j];
			model = fish.get_model_mat();
			glUniform3f(glGetUniformLocation(fishShader.ID, "fishColor"), color.x, color.y, color.z);
			glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniform3f(glGetUniformLocation(fishShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

			//"Animation"
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(sin(glm::radians(fish.swimCycle *16))/16, sin(glm::radians(fish.swimCycle * 16))/ 16, 0));

			glm::mat4 rot = glm::rotate((float)cos(glm::radians(fish.swimCycle *16))/8, glm::vec3(0, 1, 0));
			rot = glm::rotate(rot,(float)cos(glm::radians(fish.swimCycle * 16)) / 16, glm::vec3(1, 0, 0));

			glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "rot"), 1, GL_FALSE, glm::value_ptr(rot));
			glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "tra"), 1, GL_FALSE, glm::value_ptr(model));

			fishMesh.Draw(fishShader, camera);
		}
	}
}

void draw_fish_smp(Mesh fishMesh, Shader fishShader, Camera camera, glm::vec3 lightPos) {
	glm::vec3 pos = glm::vec3(0.0f, 5.0f, 0.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);

	glUniform3f(glGetUniformLocation(fishShader.ID, "fishColor"),	1.0f, 1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform3f(glGetUniformLocation(fishShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	fishMesh.Draw(fishShader, camera);
}

bool pasuseBoids = false;

bool fish_cam = false;

int shoalId = 0;
int fsihId = 0;

Fish dummy = Fish();

Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f), &dummy);


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		pasuseBoids = !pasuseBoids;

	if (key == GLFW_KEY_F && action == GLFW_PRESS) { //Enter fish cam
		camera.fishCam = true;
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS) //Quit fish cam
		camera.fishCam = false;
}


int main()
{
	std::vector<Vertex> fishVertices = std::vector<Vertex>();
	std::vector<GLuint> fishIndices = std::vector<GLuint>();

	//read_obj(fishVertices, fishIndices);
	loadOBJ("models/fish.obj", fishVertices, fishIndices);

	//print_vec3_list(vertices);

	//print_ver(fishVertices);

	std::vector <Shoal> sholes = std::vector<Shoal>();

	glm::vec3 colors[] = {
		glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0),
		glm::vec3(0.0, 0.0, 1.0),
	};
	for (int i = 0; i < 3; i++) {

		Shoal shoal = Shoal(colors[i]);

		for (int j = 0; j < 150; j++) {
			shoal.add(Fish());
		}

		sholes.push_back(shoal);
	}

	camera.setFish(&sholes[0].get()[0]);

	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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
	glfwSetKeyCallback(window, key_callback);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	glViewport(0, 0, width, height);


	// Original code from the tutorial
	Texture textures[]
	{
		Texture("textures/sea_sand.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
	};

	Texture fish_textures[]
	{
		Texture("textures/fish_texture.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
	};


	Shader shaderProgram("default.vert", "default.frag");
	std::vector <Vertex> verts(vertices_floor, vertices_floor + sizeof(vertices_floor) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));

	std::vector <Texture> fish_tex(fish_textures, fish_textures + sizeof(fish_textures) / sizeof(Texture));

	//std::vector <Texture> fish_tex(tex, tex + sizeof(tex) / sizeof(Texture));

	// Create floor mesh
	Mesh floor(verts, ind, tex);

	//Fishe
	//Shader fishShader("fish.vert", "fish.frag");
	Shader fishShader("fish.vert", "fish.frag");

	Mesh fish(fishVertices, fishIndices, fish_tex);

	Shader lightShader("light.vert", "light.frag");
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInd, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 40.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	//glEnable(GL_DEPTH_TEST);

	fishShader.Activate();

	objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);
	objectModel = glm::rotate(objectModel, (float)PI/16, glm::vec3(0, 1, 0));

	glUniform3f(glGetUniformLocation(fishShader.ID, "fishColor"), 1.0f, 1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform3f(glGetUniformLocation(fishShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glEnable(GL_DEPTH_TEST);

	// Creates camera object


	BoidsController boidsController = BoidsController();
	//boidsController.initBoids(0, PI / 2, PI / 2, numBoids, fish_list);
	boidsController.initBoids(0, 0, 0, sholes);

	double prevTime = glfwGetTime();

	// Main while loop
	while (!glfwWindowShouldClose(window)){

		double crntTime = glfwGetTime();
		//60ps boids
		if (crntTime - prevTime >= 1 / 60)
		{
			if (!pasuseBoids) {
				boidsController.update(sholes);
			}

			prevTime = crntTime;
		}

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.37f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 500.0f);

		// Draws different meshes
		lightShader.Activate();
		light.Draw(lightShader, camera);

		shaderProgram.Activate();
		floor.Draw(shaderProgram, camera);

		//fishShader.Activate();
		//glUniform3f(glGetUniformLocation(fishShader.ID, "fishColor"), 1.0f, 0.0f, 0.0f);
		//glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
		//glUniform3f(glGetUniformLocation(fishShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		//fish.Draw(fishShader, camera);


		fishShader.Activate();
		draw_fish(fish, fishShader, camera, lightPos, sholes);

		//objectModel = glm::mat4(1.0f);
		//objectModel = glm::translate(objectModel, glm::vec3(sin(glm::radians(rotation*16))/8, 2.0 + sin(glm::radians(rotation * 8))/ 16, 0));

		//glm::mat4 rot = glm::rotate(cos(glm::radians(rotation*16))/8, glm::vec3(0, 1, 0));
		//rot = glm::rotate(rot, cos(glm::radians(rotation * 8)) / 16, glm::vec3(1, 0, 0));

		//glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "rot"), 1, GL_FALSE, glm::value_ptr(rot));
		//glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));

		//fish.Draw(fishShader, camera);

		//newShader.Activate();
		//draw_fish_smp(fish, fishShader, camera, lightPos);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	shaderProgram.Delete();
	lightShader.Delete();
	fishShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}