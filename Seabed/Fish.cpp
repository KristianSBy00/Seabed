#include"Fish.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

# define PI           3.14159265358979323846 

Fish::Fish() {
	Fish::id = 0;

	Fish::x = 0.0;
	Fish::y = 0.0;
	Fish::z = 0.0;

	Fish::d_x = 0;
	Fish::d_y = 0;
	Fish::d_z = 0;

	Fish::rot_x = 0;
	Fish::rot_y = 0;
	Fish::rot_z = 0;
}

Fish::Fish(double rot_x, double rot_y, double rot_z) {
	Fish::id = 0;

	Fish::x = 0.0;
	Fish::y = 0.0;
	Fish::z = 0.0;

	Fish::d_x = 0;
	Fish::d_y = 0;
	Fish::d_z = 0;

	Fish::rot_x = rot_x;
	Fish::rot_y = rot_y;
	Fish::rot_z = rot_z;
}

double Fish::CalcHeadingRad() {
	double length_2d = sqrt(d_x * d_x + d_z * d_z);

	double hdg = 0;

	if (length_2d > 0)
	{
		double v_x = d_x / length_2d;
		double v_z = d_z / length_2d;

		if (v_z == 0.0)
		{
			if (v_x >= 0.0) hdg = PI / 2;
			else hdg = 3 * PI / 2;
		}
		else hdg = atan(v_x / v_z); //atan2?

		if (v_z < 0) hdg += PI;
		if (hdg < 0) hdg += 2 * PI;

	}
	return hdg;
}
double Fish::CalcPitchRad() {
	double length_2d = sqrt(d_x * d_x + d_z * d_z);
	double pitch = 0;

	if (length_2d == 0) {
		return pitch;
	}

	pitch = atan(d_y / length_2d); //atan2?
	return pitch;
}

glm::mat4 Fish::get_rotation_mat() {
	double hor_angle = CalcHeadingRad();
	double pitch = CalcPitchRad();

	glm::mat4 rot_mat_x = glm::rotate(float(rot_x), glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 rot_mat_y = glm::rotate(float(hor_angle + rot_y), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 rot_mat_z = glm::rotate(float(-pitch + rot_z), glm::vec3(0.0, 0.0, 1.0));

	return rot_mat_y * rot_mat_x * rot_mat_z;;
}
glm::mat4 Fish::get_translation_mat() {
	return glm::translate(glm::vec3(x, y, z));
}
glm::mat4 Fish::get_model_mat() {
	glm::mat4 ident = glm::mat4(1.0f);
	return ident * get_translation_mat() * get_rotation_mat();
	//return ident * get_translation_mat() * get_rotation_mat();
}

glm::vec3 Fish::get_rot_vec() {
	double hor_angle = CalcHeadingRad();
	double pitch = CalcPitchRad();

	return glm::vec3(float(rot_x), float(hor_angle + rot_y), float(-pitch + rot_z));

}

glm::vec3 Fish::get_position_vec() {
	return glm::vec3(x, y, z);

}