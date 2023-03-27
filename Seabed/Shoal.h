#ifndef SHOAL_CLASS_H
#define SHOAL_CLASS_H

#include<glm/glm.hpp>
#include<vector>

#include"Fish.h"

class Shoal {
public:
	std::vector <Fish> fish;
	glm::vec3 color;
	bool preadator;

	Shoal(glm::vec3 init_color);
	void add(Fish new_fish);
	std::vector<Fish>& get();
};
#endif