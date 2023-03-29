#include"Mesh.h"
#include"boidsController.h"

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

void tokenize(std::string const& str, const char delim,
	std::vector<std::string>& out)
{
	// construct a stream from the string 
	std::stringstream ss(str);

	std::string s;
	while (std::getline(ss, s, delim)) {
		out.push_back(s);
	}
}


void read_obj(std::vector<Vertex>& vertices_for_func, std::vector<GLuint>& indices_for_func) {
	string line;
	ifstream myfile("fish.obj");

	const char delim = ' ';
	const char delim2 = '/';

	std::vector<glm::vec3> vertices_buffer = std::vector<glm::vec3>();
	std::vector<glm::vec3> norm_buffer = std::vector<glm::vec3>();
	std::vector<glm::vec2> tex_buffer = std::vector<glm::vec2>();

	std::vector<GLuint> norm_indices = std::vector<GLuint>();

	if (myfile.is_open()){
		while (getline(myfile, line)){
			if (line.rfind("vn", 0) == 0) {
				line.erase(0, 3); //remove "v "
				glm::vec3 new_vec = glm::vec3();

				std::vector<std::string> out;
				tokenize(line, delim, out);

				for (int i = 0; i < 3; i++) {
					new_vec[i] = std::stof(out[i]);
				}
				norm_buffer.push_back(new_vec);
			}

			else if (line.rfind("vt", 0) == 0) {
				line.erase(0, 3); //remove "v "
				glm::vec2 new_vec = glm::vec2();

				std::vector<std::string> out;
				tokenize(line, delim, out);

				for (int i = 0; i < 2; i++) {
					new_vec[i] = std::stof(out[i]);
				}
				tex_buffer.push_back(new_vec);
			}

			else if (line.rfind("v", 0) == 0) {
				line.erase(0, 2); //remove "v "

				glm::vec3 new_vec = glm::vec3();

				std::vector<std::string> out;
				tokenize(line, delim, out);

				for (int i = 0; i < 3; i++) {
					new_vec[i] = std::stof(out[i]);
				}
				vertices_buffer.push_back(new_vec);
			}

			else if (line.rfind("f", 0) == 0) {
				line.erase(0, 2); //remove "v "
				std::vector<std::string> out;
				tokenize(line, delim, out);
				for (auto& s : out) {
					std::vector<std::string> out2;
					tokenize(s, delim2, out2);
					unsigned int num;
					num = stoi(out2[0]);
					indices_for_func.push_back(num-1);

					num = stoi(out2[1]);
					norm_indices.push_back(num - 1);
				}
			}
		}
		myfile.close();

		for (int i = 0; i < vertices_buffer.size(); i++) {
			Vertex vertex_to_add = { vertices_buffer[i], glm::vec3(1.0f, 1.0f, 1.0f), norm_buffer[i], tex_buffer [i]};
			vertices_for_func.push_back(vertex_to_add);
		}
	}
	else cout << "Unable to open file";

}


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
	Vertex{glm::vec3(-20.0f, 0.0f,  20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-20.0f, 0.0f, -20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(20.0f, 0.0f, -20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(20.0f, 0.0f,  20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)}
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


void newLoadOBJ(const char* path, std::vector<Vertex>& vertices_for_func, std::vector<GLuint>& indices_for_func) {
	string line;
	ifstream myfile(path);

	const char delim = ' ';
	const char delim2 = '/';

	std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line.rfind("vn", 0) == 0) {
				line.erase(0, 3); //remove "v "
				glm::vec3 new_vec = glm::vec3();

				std::vector<std::string> out;
				tokenize(line, delim, out);

				for (int i = 0; i < 3; i++) {
					new_vec[i] = std::stof(out[i]);
				}
				temp_normals.push_back(new_vec);
			}

			else if (line.rfind("vt", 0) == 0) {
				line.erase(0, 3); //remove "v "
				glm::vec2 new_vec = glm::vec2();

				std::vector<std::string> out;
				tokenize(line, delim, out);

				for (int i = 0; i < 2; i++) {
					new_vec[i] = std::stof(out[i]);
				}
				temp_uvs.push_back(new_vec);
			}

			else if (line.rfind("v", 0) == 0) {
				line.erase(0, 2); //remove "v "

				glm::vec3 new_vec = glm::vec3();

				std::vector<std::string> out;
				tokenize(line, delim, out);

				for (int i = 0; i < 3; i++) {
					new_vec[i] = std::stof(out[i]);
				}
				temp_vertices.push_back(new_vec);
			}

			else if (line.rfind("f", 0) == 0) {
				line.erase(0, 2); //remove "v "
				std::vector<std::string> out;
				tokenize(line, delim, out);
				for (auto& s : out) {
					std::vector<std::string> out2;
					tokenize(s, delim2, out2);

					unsigned int num;

					num = stoi(out2[0]);
					vertexIndices.push_back(num);

					num = stoi(out2[2]);
					normalIndices.push_back(num);

					num = stoi(out2[1]);
					uvIndices.push_back(num);
				}
			}
		}
		myfile.close();
	}
	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		vertices_for_func.push_back(Vertex{ vertex , glm::vec3(1.0f, 1.0f, 1.0f) , normal, uv });
		indices_for_func.push_back(i);

	}
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		pasuseBoids = !pasuseBoids;
}


int main()
{
	std::vector<Vertex> fishVertices = std::vector<Vertex>();
	std::vector<GLuint> fishIndices = std::vector<GLuint>();

	//read_obj(fishVertices, fishIndices);
	newLoadOBJ("fish.obj", fishVertices, fishIndices);

	//print_vec3_list(vertices);

	print_ver(fishVertices);

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
		Texture("sand.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
	};

	Texture fish_textures[]
	{
		Texture("fish_texture.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
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

	objectPos = glm::vec3(0.0f, 4.0f, 0.0f);
	objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	glUniform3f(glGetUniformLocation(fishShader.ID, "fishColor"), 1.0f, 1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform3f(glGetUniformLocation(fishShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	BoidsController boidsController = BoidsController();
	//boidsController.initBoids(0, PI / 2, PI / 2, numBoids, fish_list);
	boidsController.initBoids(0, PI, 0, sholes);

	// Main while loop
	while (!glfwWindowShouldClose(window)){
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

		if (!pasuseBoids) {
			boidsController.update(sholes);
		}

		fishShader.Activate();
		draw_fish(fish, fishShader, camera, lightPos, sholes);

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