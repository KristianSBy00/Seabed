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


void Shoal::calcBound() {
	double max_x = fish[0].x;
	double min_x = fish[0].x;

	double max_y = fish[0].y;
	double min_y = fish[0].y;

	double max_z = fish[0].z;
	double min_z = fish[0].z;

	for (int i = 0; i < fish.size(); i++) {
		if (fish[i].x > max_x) max_x = fish[i].x;
		if (fish[i].x < min_x) min_x = fish[i].x;

		if (fish[i].y > max_y) max_y = fish[i].y;
		if (fish[i].y < min_y) min_y = fish[i].y;

		if (fish[i].z > max_z) max_z = fish[i].z;
		if (fish[i].z < min_z) min_z = fish[i].z;
	}

	bounds.max_x = max_x;
	bounds.min_x = min_x;

	bounds.max_y = max_y;
	bounds.min_y = min_y;

	bounds.max_z = max_z;
	bounds.min_z = min_z;
}


void Shoal::incrementCoherence() {
	Shoal::coherence = Shoal::coherence * 2;

	if (Shoal::coherence > 0.1) {
		Shoal::coherence = 0.1;
	}
	printf("Coherence %f\n", Shoal::coherence);
}
void Shoal::decrementCoherence() {
	Shoal::coherence = Shoal::coherence / 2;

	if (Shoal::coherence < 0.000390625) {
		Shoal::coherence = 0.000390625;
	}
	printf("Coherence %f\n", Shoal::coherence);
}

void Shoal::incrementSeparation() {
	Shoal::separation = Shoal::separation * 2;

	if (Shoal::separation > 0.1) {
		Shoal::separation = 0.1;
	}
	printf("Separation %f\n", Shoal::separation);
}
void Shoal::decrementSeparation() {
	Shoal::separation = Shoal::separation / 2;

	if (Shoal::separation < 0.000390625) {
		Shoal::separation = 0.000390625;
	}
	printf("Separation %f\n", Shoal::separation);
}

void Shoal::incrementAlignment() {
	Shoal::alignment = Shoal::alignment * 2;

	if (Shoal::alignment > 0.1) {
		Shoal::alignment = 0.1;
	}
	printf("Alignment %f\n", Shoal::alignment);
}
void Shoal::decrementAlignment() {
	Shoal::alignment = Shoal::alignment / 2;

	if (Shoal::alignment < 0.000390625) {
		Shoal::alignment = 0.000390625;
	}
	printf("Alignment %f\n", Shoal::alignment);
}

void Shoal::incrementVisualRange() {
	Shoal::visualRange = Shoal::visualRange * 2;

	if (Shoal::visualRange > 38.4) {
		Shoal::visualRange = 38.4;
	}
	printf("Visual Range %f\n", Shoal::visualRange);
}
void Shoal::decrementVisualRange() {
	Shoal::visualRange = Shoal::visualRange / 2;

	if (Shoal::visualRange < 0.225) {
		Shoal::visualRange = 0.225;
	}
	printf("Visual Range %f\n", Shoal::visualRange);
}