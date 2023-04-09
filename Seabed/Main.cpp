#include"Mesh.h"
#include"boidsController.h"
#include "obj.h"
#include "Kelp.h"

# define PI           3.14159265358979323846  /* pi */

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

#include <glm/glm.hpp>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <chrono>
#define GLM_ENABLE_EXPERIMENTAL

using namespace std;
const unsigned int width = 1366;
const unsigned int height = 768;


Vertex vertices_floor[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-30.0f, 0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-30.0f, 0.0f, -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(30.0f, 0.0f, -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(30.0f, 0.0f,  30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}
};



// Indices for vertices order
GLuint indices_floor[] =
{
	0, 1, 2,
	0, 2, 3
};


Vertex vertices_walls[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-30.f, -0.5, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-30.f, -0.5, -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-30.f, 25.0f, -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(-30.f, 25.0f,  30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(30.f, -0.5, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(30.f, -0.5, -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(30.f, 25.0f, -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(30.f, 25.0f,  30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(30.f, -0.5, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-30.f, -0.5, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-30.f, 25.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(30.f, 25.0f,  30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},

	Vertex{glm::vec3(30.f, -0.5, -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-30.f, -0.5, -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-30.f, 25.0f, -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(30.f, 25.0f,  -30.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)}
};


GLuint indices_walls[] =
{
	//0, 1, 2,
	//0, 2, 3

	3, 2, 0,
	2, 1, 0,

	4, 5, 6,
	4, 6, 7,

	8, 9, 10,
	8, 10, 11,

	12, 13, 14,
	12, 14, 15
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


void expandFloor(std::vector<Vertex>& base, std::vector<Vertex>& out) {
	for (int i = -3; i < 3; i++) {
		for (int j = -3; j < 3; j++) {
			for (int k = 0; k < base.size(); k++) {

				glm::vec3 vertex	= base[k].position;
				glm::vec3 clor		= base[k].color;
				glm::vec3 normal	= base[k].color;
				glm::vec2 uv		= base[k].texUV;

				glm::vec3 newVertex = glm::vec3(vertex.x + i*10, vertex.y, vertex.z + j*10);
				out.push_back(Vertex{ newVertex, clor, normal, uv });
			}
		}	
	}
}


void draw_fish(Mesh fishMesh, Shader fishShader, Camera camera, std::vector<Shoal>& sholes_in) {
	glm::mat4 model;
	//glm::vec3 pyPos;

	int index = 0;

	for (int i = 0; i < sholes_in.size(); i++) {

		std::vector<Fish>& shole = sholes_in[i].get();

		glm::vec3 color = sholes_in[i].color;

		for (int j = 0; j < shole.size(); j++) {

			Fish& fish = shole[j];
			model = fish.get_model_mat();
			//glm::vec3 pyPos = fish.get_position_vec();

			//printf("pyPos <%f, %f, %f>\n", pyPos.x, pyPos.y, pyPos.z);

			glUniform3f(glGetUniformLocation(fishShader.ID, "fishColor"), color.x, color.y, color.z);
 			glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniform1i(glGetUniformLocation(fishShader.ID, "fishId"), fish.id);

			//"Animation"
			glUniform1f(glGetUniformLocation(fishShader.ID, "swimCycle"), fish.swimCycle);
			//glUniform3f(glGetUniformLocation(fishShader.ID, "pyPos"), pyPos.x, pyPos.y, pyPos.z);

			fishMesh.Draw(fishShader, camera);
			index++;
		}
	}
}


void draw_demo_fish(Mesh fishMesh, Shader fishShader, Camera camera, float debugFishCycle) {
	glm::mat4 model = glm::mat4(1.f);
	glm::vec3 pyPos = glm::vec3(0.0, -5.0, 0.0);

	model = glm::translate(model, pyPos);

	glUniform3f(glGetUniformLocation(fishShader.ID, "fishColor"), 1.0f, 1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1i(glGetUniformLocation(fishShader.ID, "fishId"), 1);
	glUniform1f(glGetUniformLocation(fishShader.ID, "swimCycle"), debugFishCycle);
	fishMesh.Draw(fishShader, camera);
}

void drawKelp(Mesh kelpMesh, Shader kelpShader, Camera camera, std::vector<Kelp>& kelpIn, float time) {
	for (int i = 0; i < kelpIn.size(); i++) {
		glm::mat4 rot_x = glm::rotate((float)sin(glm::radians(kelpIn[i].cycle * 8)) / 8, glm::vec3(1, 0, 0));
		glm::mat4 rot_y = glm::rotate((float)cos(glm::radians(kelpIn[i].cycle * 4)) / 4, glm::vec3(0, 1, 0));
		glm::mat4 rot_z = glm::rotate((float)cos(glm::radians(kelpIn[i].cycle * 8)) / 8, glm::vec3(0, 0, 1));

		glm::mat4 currentRot = glm::rotate((float)sin(glm::radians(kelpIn[i].cycle * 8)) / 8 + 1.f/2, glm::vec3(-1, 0, 1));

		glUniformMatrix4fv(glGetUniformLocation(kelpShader.ID, "rot_x"), 1, GL_FALSE, glm::value_ptr(rot_x));
		glUniformMatrix4fv(glGetUniformLocation(kelpShader.ID, "rot_y"), 1, GL_FALSE, glm::value_ptr(rot_y));
		glUniformMatrix4fv(glGetUniformLocation(kelpShader.ID, "rot_z"), 1, GL_FALSE, glm::value_ptr(rot_z));
		glUniformMatrix4fv(glGetUniformLocation(kelpShader.ID, "currentRot"), 1, GL_FALSE, glm::value_ptr(currentRot));

		glm::mat4 baseRot = glm::rotate( (float) kelpIn[i].rotation, glm::vec3(0, 1, 0) );
		float size		= kelpIn[i].size;
		float lenght	= kelpIn[i].lenght;
		glm::mat4 translation = glm::translate(kelpIn[i].pos);

		glUniform1f(glGetUniformLocation(kelpShader.ID, "cycle"), kelpIn[i].cycle);
		glUniformMatrix4fv(glGetUniformLocation(kelpShader.ID, "baseRot"), 1, GL_FALSE, glm::value_ptr(baseRot));
		glUniform1f(glGetUniformLocation(kelpShader.ID, "size"), size);
		glUniform1f(glGetUniformLocation(kelpShader.ID, "lenght"), lenght);
		glUniformMatrix4fv(glGetUniformLocation(kelpShader.ID, "trans"), 1, GL_FALSE, glm::value_ptr(translation));
		glUniform1f(glGetUniformLocation(kelpShader.ID, "time"), time);
		kelpMesh.Draw(kelpShader, camera);
	}
}

bool pasuseBoids = false;
bool fish_cam = false;
float kelpCycle = 0;
int shoalId = 0;
int fsihId = 0;

Fish dummy = Fish();

Camera camera(width, height, glm::vec3(0.0f, 5.0f, 30.0f), &dummy);

BoidsController boidsController = BoidsController();

std::vector <Shoal> sholes = std::vector<Shoal>();

std::vector <Kelp> theKelp = std::vector<Kelp>();

bool is_left_down = false;
bool is_right_down = false;

bool is_V_down = false;
bool is_A_down = false;
bool is_S_down = false;
bool is_C_down = false;

int shoal_index = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Shoal index
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)	shoal_index = 0;
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)	shoal_index = 1;
	if (key == GLFW_KEY_3 && action == GLFW_PRESS)	shoal_index = 2;

	//Shoal holdowns
	if (key == GLFW_KEY_LEFT)	is_left_down	= action == GLFW_PRESS;
	if (key == GLFW_KEY_RIGHT)	is_right_down	= action == GLFW_PRESS;

	if (key == GLFW_KEY_V)		is_V_down		= action == GLFW_PRESS;
	if (key == GLFW_KEY_A)		is_A_down		= action == GLFW_PRESS;
	if (key == GLFW_KEY_S)		is_S_down		= action == GLFW_PRESS;
	if (key == GLFW_KEY_C)		is_C_down		= action == GLFW_PRESS;



	//Boids controll
	if (is_V_down) {
		if (is_right_down)		sholes[shoal_index].incrementVisualRange();
		else if (is_left_down)	sholes[shoal_index].decrementVisualRange();
	}
	if (is_A_down) {
		if (is_right_down)		sholes[shoal_index].incrementAlignment();
		else if (is_left_down)	sholes[shoal_index].decrementAlignment();
	}
	if (is_S_down) {
		if (is_right_down)		sholes[shoal_index].incrementSeparation();
		else if (is_left_down)	sholes[shoal_index].decrementSeparation();
	}
	if (is_C_down) {
		if (is_right_down)		sholes[shoal_index].incrementCoherence();
		else if (is_left_down)	sholes[shoal_index].decrementCoherence();
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		pasuseBoids = !pasuseBoids;

	if (key == GLFW_KEY_F && action == GLFW_PRESS) { //Enter fish cam
		camera.fishCam = true;
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS) //Quit fish cam
		camera.fishCam = false;
}

void fishToShader(Shader shader) {
	for (int i = 0; i < sholes.size(); i++) {

		Shoal shoal = sholes[i];

		for (int j = 0; j < sholes[i].get().size(); j++) {

			string location = "fish[" + std::to_string(sholes[i].get()[j].id) + "]";

			double x = sholes[i].get()[j].x;
			double y = sholes[i].get()[j].y;
			double z = sholes[i].get()[j].z;

			glUniform3f(glGetUniformLocation(shader.ID, location.data()), x, y, z);
		}
	}
}

int main()
{
	std::vector<Vertex> fishVertices = std::vector<Vertex>();
	std::vector<GLuint> fishIndices = std::vector<GLuint>();

	std::vector<Vertex> rockVertices = std::vector<Vertex>();
	std::vector<GLuint> rockIndices = std::vector<GLuint>();

	std::vector<Vertex> kelpVertices = std::vector<Vertex>();
	std::vector<GLuint> kelpIndices = std::vector<GLuint>();

	std::vector<Vertex> boxVertices = std::vector<Vertex>();
	std::vector<GLuint> boxIndices = std::vector<GLuint>();

	std::vector<Vertex> sunVertices = std::vector<Vertex>();
	std::vector<GLuint> sunIndices = std::vector<GLuint>();

	std::vector<Vertex> wallVertices(vertices_walls, vertices_walls + sizeof(vertices_walls) / sizeof(Vertex));
	std::vector<GLuint> wallIndices(indices_walls, indices_walls + sizeof(indices_walls) / sizeof(GLuint));

	std::vector <Vertex> floorVertices(vertices_floor, vertices_floor + sizeof(vertices_floor) / sizeof(Vertex));
	std::vector <GLuint> floorIndices(indices_floor, indices_floor + sizeof(indices_floor) / sizeof(GLuint));

	loadOBJ("models/fish.obj", fishVertices, fishIndices);
	loadOBJ("models/bigrock.obj", rockVertices, rockIndices);
	loadOBJ("models/kelp.obj", kelpVertices, kelpIndices);
	loadOBJ("models/theBox.obj", boxVertices, boxIndices);
	loadOBJ("models/golf.obj", sunVertices, sunIndices);

	for (int i = 0; i < rockVertices.size(); i++) {
		boidsController.addObsticle(rockVertices[i].position);
	}

	boidsController.calcBound();

	glm::vec3 colors[] = {
		glm::vec3(1.0, 0.0, 0.0),
		glm::vec3(0.0, 1.0, 0.0),
		glm::vec3(0.0, 0.0, 1.0),
	};
	for (int i = 0; i < 3; i++) {

		Shoal shoal = Shoal(colors[i]);

		for (int j = 0; j < 100; j++) {
			shoal.add(Fish());
		}

		sholes.push_back(shoal);
	}


	for (int i = 0; i < 500; i++) {
		theKelp.push_back(Kelp(boidsController.getBound(), theKelp));
	}

	camera.setFish(&sholes[0].get()[0]);

	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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
	Texture floorTextures[]
	{
		Texture("textures/Stylized_Sand_001_basecolor.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("textures/Stylized_Sand_001_height.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/Stylized_Sand_001_normal.png", "normals", 2, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/disortionmap.png", "dissortion", 3, GL_RED, GL_UNSIGNED_BYTE),
	};

	Texture rockTextures[]
	{
		Texture("textures/Sea_Rock_001_BaseColor.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("textures/Sea_Rock_001_Height.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/Sea_Rock_001_Normal.png", "normals", 2, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("textures/disortionmap.png", "dissortion", 3, GL_RED, GL_UNSIGNED_BYTE),
	};

	Texture kelpTextures[]
	{
		Texture("textures/Coral_002_basecolor.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("textures/Coral_002_height.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/Coral_002_normal.png", "normals", 2, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("textures/disortionmap.png", "dissortion", 3, GL_RED, GL_UNSIGNED_BYTE),
	};

	Texture fish_textures[]
	{
		Texture("textures/fish_texture.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		//Dummy textures that wont be used
		Texture("textures/Coral_002_height.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/Coral_002_normal.png", "normals", 2, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("textures/disortionmap.png", "dissortion", 3, GL_RED, GL_UNSIGNED_BYTE),
	};

	Texture surfaceTextures[]
	{
		Texture("textures/fish_texture.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("textures/Coral_002_height.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/NormalMap.png", "normals", 2, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("textures/disortionmap.png", "dissortion", 3, GL_RED, GL_UNSIGNED_BYTE),
	};

	Texture cus[]
	{
		Texture("textures/caustics/nr1.png", "caustics", 4, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr2.png", "caustics", 5, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr3.png", "caustics", 6, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr4.png", "caustics", 7, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr5.png", "caustics", 8, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr6.png", "caustics", 9, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr7.png", "caustics", 10, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr8.png", "caustics", 11, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr9.png", "caustics", 12, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr10.png", "caustics", 13, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr11.png", "caustics", 14, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr12.png", "caustics", 15, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr13.png", "caustics", 16, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr14.png", "caustics", 17, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr15.png", "caustics", 18, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr16.png", "caustics", 19, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr17.png", "caustics", 20, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr18.png", "caustics", 21, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr19.png", "caustics", 22, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr20.png", "caustics", 23, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr21.png", "caustics", 24, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr22.png", "caustics", 25, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr23.png", "caustics", 26, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr24.png", "caustics", 27, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr25.png", "caustics", 28, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr26.png", "caustics", 29, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr27.png", "caustics", 30, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr28.png", "caustics", 31, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr29.png", "caustics", 32, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr30.png", "caustics", 33, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr31.png", "caustics", 34, GL_RED, GL_UNSIGNED_BYTE),
		Texture("textures/caustics/nr32.png", "caustics", 35, GL_RED, GL_UNSIGNED_BYTE),
	};

	Texture norms[]
	{
		Texture("textures/surfaceNormals/nr1.png", "caustics", 36, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr2.png", "caustics", 37, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr3.png", "caustics", 38, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr4.png", "caustics", 39, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr5.png", "caustics", 40, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr6.png", "caustics", 41, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr7.png", "caustics", 42, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr8.png", "caustics", 43, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr9.png", "caustics", 44, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr10.png", "caustics", 45, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr11.png", "caustics", 46, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr12.png", "caustics", 47, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr13.png", "caustics", 48, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr14.png", "caustics", 49, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr15.png", "caustics", 50, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr16.png", "caustics", 51, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr17.png", "caustics", 52, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr18.png", "caustics", 53, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr19.png", "caustics", 54, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr20.png", "caustics", 55, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr21.png", "caustics", 56, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr22.png", "caustics", 57, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr23.png", "caustics", 58, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr24.png", "caustics", 59, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr25.png", "caustics", 60, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr26.png", "caustics", 61, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr27.png", "caustics", 62, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr28.png", "caustics", 63, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr29.png", "caustics", 64, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr30.png", "caustics", 65, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr31.png", "caustics", 66, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("textures/surfaceNormals/nr32.png", "caustics", 67, GL_RGB, GL_UNSIGNED_BYTE),
	};

	std::vector<Texture>	floorTex(floorTextures, floorTextures + sizeof(floorTextures) / sizeof(Texture));
	std::vector<Texture>	fish_tex(fish_textures, fish_textures + sizeof(fish_textures) / sizeof(Texture));
	std::vector<Texture>	rockTex(rockTextures, rockTextures + sizeof(rockTextures) / sizeof(Texture));
	std::vector<Texture>	kelpTex(kelpTextures, kelpTextures + sizeof(kelpTextures) / sizeof(Texture));
	std::vector<Texture>	surfaceTex(surfaceTextures, surfaceTextures + sizeof(surfaceTextures) / sizeof(Texture));
	std::vector<Texture>	nromalTex(norms, norms + sizeof(norms) / sizeof(Texture));

	std::vector<Texture>	castics(cus, cus + sizeof(cus) / sizeof(Texture));

	std::vector<Texture>    emptTex = std::vector<Texture>();

	Shader floorShader("default.vert", "default.frag");
	Shader rockShader("default.vert", "default.frag");
	Shader fishShader("fish.vert", "fish.frag");
	Shader kelpShader("kelp.vert", "kelp.frag");
	Shader waterSurfaceShader("waterSurface.vert", "waterSurface.frag");
	Shader sunShader("sun.vert", "sun.frag");
	Shader boxShader("box.vert", "box.frag");

	Mesh waterSurface = Mesh(floorVertices, floorIndices, surfaceTex, castics, nromalTex);
	Mesh floor = Mesh(floorVertices, floorIndices, floorTex, castics, emptTex);
	Mesh rock = Mesh(rockVertices, rockIndices, rockTex, castics, emptTex);
	Mesh fish = Mesh(fishVertices, fishIndices, fish_tex, castics, emptTex);
	Mesh kelp = Mesh(kelpVertices, kelpIndices, kelpTex, castics, emptTex);
	Mesh sun = Mesh(sunVertices, sunIndices, floorTex, emptTex, emptTex);
	Mesh box  = Mesh(wallVertices, wallIndices, floorTex, castics, emptTex);


	std::vector<Mesh> meshList = std::vector<Mesh>();
	std::vector<glm::vec3> posList = std::vector<glm::vec3>();

	meshList.push_back(waterSurface);
	meshList.push_back(floor);
	meshList.push_back(rock);
	meshList.push_back(fish);
	meshList.push_back(sun);
	meshList.push_back(box);
	//meshList.push_back(box);


	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	waterSurfaceShader.Activate();
	objectPos = glm::vec3(0.0f, 25.0f, 0.0f);
	objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);
	glUniformMatrix4fv(glGetUniformLocation(waterSurfaceShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform1f(glGetUniformLocation(waterSurfaceShader.ID, "texRep"), 0.0);

	objectModel = glm::mat4(1.0f);
	floorShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(floorShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform1i(glGetUniformLocation(floorShader.ID, "texRep"), 4);

	rockShader.Activate();
	glm::mat4 objectModeler = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(rockShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModeler));
	glUniform1i(glGetUniformLocation(rockShader.ID, "texRep"), 8);

	objectModel = glm::mat4(1.0f);
	boxShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(boxShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));

	sunShader.Activate();
	objectPos = glm::vec3(0.0f, 100.0f, 0.0f);
	objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);
	glUniformMatrix4fv(glGetUniformLocation(sunShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform1i(glGetUniformLocation(sunShader.ID, "texRep"), 0);

	//boxShader.Activate();
	//objectModeler = glm::mat4(1.0f);
	kelpShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(kelpShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModeler));

	fishShader.Activate();
	objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);
	objectModel = glm::rotate(objectModel, (float)PI/16, glm::vec3(0, 1, 0));
	glUniform3f(glGetUniformLocation(fishShader.ID, "fishColor"), 1.0f, 1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	//glUniform3f(glGetUniformLocation(fishShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Creates camera object

	boidsController.initBoids(0, 0, 0, sholes);
	double prevTime = glfwGetTime();
	float debugFishCycle = 0;

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

			for (int i = 0; i < theKelp.size(); i++) {
				theKelp[i].pushCycle(0.5 + theKelp[i].size/2 );
				//theKelp[i].pushCycle(0.2);
			}

			floor.uppdate_caustics();
			fish.uppdate_caustics();
			rock.uppdate_caustics();
			waterSurface.uppdate_caustics();
			box.uppdate_caustics();

			debugFishCycle += 0.3;

		}

		glClearColor(1.f, 1.f, 1.f, 1.f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 200.0f);


		sunShader.Activate();
		glUniform1f(glGetUniformLocation(sunShader.ID, "time"), glfwGetTime());
		sun.Draw(sunShader, camera);

		kelpShader.Activate();
		fishToShader(kelpShader);
		drawKelp(kelp, kelpShader, camera, theKelp, glfwGetTime());

		rockShader.Activate();
		fishToShader(rockShader);
		glUniform1f(glGetUniformLocation(rockShader.ID, "time"), glfwGetTime());
		rock.Draw(rockShader, camera);

		floorShader.Activate();
		glUniform1f(glGetUniformLocation(floorShader.ID, "time"), glfwGetTime());
		fishToShader(floorShader);
		floor.Draw(floorShader, camera);

		fishShader.Activate();
		fishToShader(kelpShader);
		glUniform1f(glGetUniformLocation(fishShader.ID, "time"), glfwGetTime());
		draw_fish(fish, fishShader, camera, sholes);
		draw_demo_fish(fish, fishShader, camera, debugFishCycle);

		waterSurfaceShader.Activate();
		glUniform1f(glGetUniformLocation(waterSurfaceShader.ID, "time"), glfwGetTime());
		waterSurface.Draw(waterSurfaceShader, camera);

		boxShader.Activate();
		glUniform1f(glGetUniformLocation(sunShader.ID, "time"), glfwGetTime());
		box.Draw(boxShader, camera);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	rockShader.Delete();
	floorShader.Delete();
	fishShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}