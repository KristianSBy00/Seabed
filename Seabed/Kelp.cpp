#include"Kelp.h"

# define PI           3.14159265358979323846 

double Kelp::fRand2(double fMin, double fMax) {
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

double Kelp::distance(double x, double z, Kelp& kelp) {
	return sqrt(
		(x - kelp.pos.x) * (x - kelp.pos.x) +
		(z - kelp.pos.z) * (z - kelp.pos.z)
	);
}


Kelp::Kelp(bound boundory, std::vector<Kelp>& otherKelp) {
	Kelp::size = Kelp::fRand2(0.5, 1.5);
	Kelp::lenght = Kelp::fRand2(0.5, 1.5);

	double x;
	double z;

	while (true) {
		x = Kelp::fRand2(-28.0, 28.0);
		z = Kelp::fRand2(-28.0, 28.0);

		if (
			(x > boundory.min_x) &&
			(x < boundory.max_x) &&
			(z > boundory.min_z) &&
			(z < boundory.max_z)) {
			continue;
		}

		bool vaid = true;

		for (int i = 0; i < otherKelp.size(); i++) {
			if (distance(x, z, otherKelp[i]) < 1.0) {
				vaid = false;
			}
		}

		if (!vaid) continue;

		Kelp::pos = glm::vec3(x, 0.0, z);

		Kelp::cycle = Kelp::fRand2(0.0, 2 * PI);
		Kelp::rotation = Kelp::fRand2(0.0, 2 * PI);
		return;
	}
}

void Kelp::pushCycle(double val) {
	Kelp::cycle += val;
}