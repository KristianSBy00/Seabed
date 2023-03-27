#include"Mesh.h"
#include"boidsController.h"

# define PI           3.14159265358979323846  /* pi */

const unsigned int width = 800;
const unsigned int height = 800;


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
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
	Vertex{glm::vec3(-20.0f, 0.0f,  20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-20.0f, 0.0f, -20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(20.0f, 0.0f, -20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(20.0f, 0.0f,  20.0f),		glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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

int numBoids = NUMBER_FISH;
Fish fish_list[NUMBER_SCOALES][NUMBER_FISH];

void draw_fish(Mesh fishMesh, Shader fishShader, Camera camera, glm::vec3 lightPos) {
	glm::mat4 model;

	float r = 0;
	float g = 0;
	float b = 0;

	for (int i = 0; i < NUMBER_SCOALES; i++) {
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

			glUniform3f(glGetUniformLocation(fishShader.ID, "fishColor"), r, g, b);
			glUniformMatrix4fv(glGetUniformLocation(fishShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniform3f(glGetUniformLocation(fishShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
			fishMesh.Draw(fishShader, camera);
		}
	}
}

int main()
{

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

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
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


	/*
	* I'm doing this relative path thing in order to centralize all the resources into one folder and not
	* duplicate them between tutorial folders. You can just copy paste the resources from the 'Resources'
	* folder and then give a relative path from this folder to whatever resource you want to get to.
	* Also note that this requires C++17, so go to Project Properties, C/C++, Language, and select C++17
	*/

	// Original code from the tutorial
	Texture textures[]
	{
		Texture("sand.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		//Texture("C:/Users/Kristian/source/repos/Seabed/Seabed/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create floor mesh
	Mesh floor(verts, ind, tex);

	//Fishe
	Shader fishShader("fish.vert", "fish.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> verts_tri(vertices_triangle, vertices_triangle + sizeof(vertices_triangle) / sizeof(Vertex));
	std::vector <GLuint> ind_tri(indices_triangle, indices_triangle + sizeof(indices_triangle) / sizeof(GLuint));
	// Create floor mesh
	Mesh fish(verts_tri, ind_tri, tex);


	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Crate light mesh
	Mesh light(lightVerts, lightInd, tex);


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 20.0f, 0.0f);
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

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	BoidsController boidsController = BoidsController();
	boidsController.initBoids(0, PI / 2, PI / 2, numBoids, fish_list);
	boidsController.initBoids(0, PI / 2, PI / 2, sholes);
	
	printf("GUY:\n");
	printf("GUY: %f\n", sholes[0].fish[0].x);
	printf("GUY:\n");

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		// Draws different meshes
		lightShader.Activate();
		light.Draw(lightShader, camera);

		shaderProgram.Activate();
		floor.Draw(shaderProgram, camera);

		fishShader.Activate();
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		boidsController.update(numBoids, fish_list);
		draw_fish(fish, fishShader, camera, lightPos);


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