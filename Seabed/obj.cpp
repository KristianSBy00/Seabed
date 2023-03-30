#include "obj.h"
#include"Mesh.h"
#include"boidsController.h"

void tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
	// construct a stream from the string 
	std::stringstream ss(str);

	std::string s;
	while (getline(ss, s, delim)) {
		out.push_back(s);
	}
}

void loadOBJ(const char* path, std::vector<Vertex>& vertices_for_func, std::vector<GLuint>& indices_for_func) {
	std::string line;
	std::ifstream myfile(path);

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