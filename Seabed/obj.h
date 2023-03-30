#pragma once
#include<string>
#include<vector>
#include"VAO.h"
#include <cstdio>
#include <stdio.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);
void loadOBJ(const char* path, std::vector<Vertex>& vertices_for_func, std::vector<GLuint>& indices_for_func);