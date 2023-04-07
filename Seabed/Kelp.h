#ifndef KELP_CLASS_H
#define KELP_CLASS_H

#include<glm/glm.hpp>
#include <cmath>
#include"Fish.h"
#include<vector>
#include"Shoal.h"

class Kelp {
public:
	double size = 1.0;
	double lenght = 1.0;
	glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
	double cycle = 0.0;
	double rotation = 0.0;


	double fRand2(double fMin, double fMax);
	Kelp(bound boundory, std::vector<Kelp>& otherKelp);
	void pushCycle(double val);
	double distance(double x, double z, Kelp& kelp);
};
#endif