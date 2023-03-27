#include"Shoal.h"

Shoal::Shoal(glm::vec3 init_color) {
	color = init_color;
}

void Shoal::add(Fish new_fish) {
	fish.push_back(new_fish);
}

std::vector <Fish>& Shoal::get() {
	return fish;
}