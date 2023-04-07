#ifndef SHOAL_CLASS_H
#define SHOAL_CLASS_H

#include<glm/glm.hpp>
#include<vector>

#include"Fish.h"

struct bound {
	double max_x;
	double min_x;

	double max_y;
	double min_y;

	double max_z;
	double min_z;
};

class Shoal {
public:
	std::vector <Fish> fish;
	glm::vec3 color;
	bool preadator;

	double coherence = 0.001;
	double separation = 0.0025;
	double alignment = 0.005;
	double visualRange = 12.5;

	bound bounds;
	Shoal(glm::vec3 init_color);
	void add(Fish new_fish);
	std::vector<Fish>& get();
	std::vector <Fish> get_new();
	void calcBound();

	void incrementCoherence();
	void decrementCoherence();

	void incrementSeparation();
	void decrementSeparation();

	void incrementAlignment();
	void decrementAlignment();

	void incrementVisualRange();
	void decrementVisualRange();


};
#endif