#ifndef FISH_CLASS_H
#define FISH_CLASS_H

#include<glm/glm.hpp>

class Fish {
public:
	int id;

	double x;
	double y;
	double z;

	double d_x;
	double d_y;
	double d_z;

	double rot_x;
	double rot_y;
	double rot_z;

	double swimCycle;

	Fish();
	Fish(double rot_x, double rot_y, double rot_z);

	double CalcHeadingRad();
	double CalcPitchRad();

	glm::mat4 get_rotation_mat();
	glm::mat4 get_translation_mat();
	glm::mat4 get_model_mat();
	glm::vec3 get_rot_vec();
	glm::vec3 get_position_vec();
};
#endif