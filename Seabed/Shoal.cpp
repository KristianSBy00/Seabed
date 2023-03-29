#include"Shoal.h"

Shoal::Shoal(glm::vec3 init_color) {
	Shoal::color = init_color;
}

void Shoal::add(Fish new_fish) {
	fish.push_back(new_fish);
}

std::vector <Fish>& Shoal::get() {
	return fish;
}

std::vector <Fish> Shoal::get_new() {
	return fish;
}