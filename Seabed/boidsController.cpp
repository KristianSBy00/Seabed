#include"boidsController.h"
#include <cmath>


BoidsController::BoidsController(double coherence, double separation, double alignment, double visualRange = 12.5) {
	BoidsController::coherence = coherence;
	BoidsController::separation = separation;
	BoidsController::alignment = alignment;
	BoidsController::visualRange = visualRange;
	BoidsController::obsticles = std::vector<glm::vec3>();
	BoidsController::boundory = bound();
}

BoidsController::BoidsController() {
	BoidsController::visualRange = 12.5;
}

double BoidsController::fRand(double fMin, double fMax) {
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


double BoidsController::distance(int school_id_1, int id_1, int school_id_2, int id_2, Fish fish_list[][NUMBER_FISH]) {
	return sqrt(
		(fish_list[school_id_1][id_1].x - fish_list[school_id_2][id_2].x) * (fish_list[school_id_1][id_1].x - fish_list[school_id_2][id_2].x) +
		(fish_list[school_id_1][id_1].y - fish_list[school_id_2][id_2].y) * (fish_list[school_id_1][id_1].y - fish_list[school_id_2][id_2].y) +
		(fish_list[school_id_1][id_1].z - fish_list[school_id_2][id_2].z) * (fish_list[school_id_1][id_1].z - fish_list[school_id_2][id_2].z)
	);
}

double BoidsController::distance(Fish& fish_1, Fish& fish_2) {
	return sqrt(
		(fish_1.x - fish_2.x) * (fish_1.x - fish_2.x) +
		(fish_1.y - fish_2.y) * (fish_1.y - fish_2.y) +
		(fish_1.z - fish_2.z) * (fish_1.z - fish_2.z)
	);
}

double BoidsController::distance(Fish& fish_1, glm::vec3 obsticle) {
	return sqrt(
		(fish_1.x - obsticle.x) * (fish_1.x - obsticle.x) +
		(fish_1.y - obsticle.y) * (fish_1.y - obsticle.y) +
		(fish_1.z - obsticle.z) * (fish_1.z - obsticle.z)
	);
}


void BoidsController::initBoids(double rot_x, double rot_y, double rot_z, int numBoids, Fish fish_list[][NUMBER_FISH]) {

	for (int i = 0; i < NUMBER_SCOALES; i++) {
		for (int j = 0; j < numBoids; j++) {
			fish_list[i][j].id = i;

			fish_list[i][j].x = fRand(-10, 10);
			fish_list[i][j].y = fRand(0.5, 15);
			fish_list[i][j].z = fRand(-10, 10);;

			fish_list[i][j].d_x = fRand(-0.1, 0.1);
			fish_list[i][j].d_y = fRand(-0.1, 0.1);
			fish_list[i][j].d_z = fRand(-0.1, 0.1);
			fish_list[i][j].swimCycle = fRand(0, 7);

			fish_list[i][j].rot_x = rot_x;
			fish_list[i][j].rot_y = rot_y;
			fish_list[i][j].rot_z = rot_z;
		}
	}
}

void BoidsController::initBoids(double rot_x, double rot_y, double rot_z, std::vector <Shoal>& sholes) {
	for (int i = 0; i < sholes.size(); i++) {
		std::vector<Fish>& shole = sholes[i].get();

		for (int j = 0; j < shole.size(); j++) {
			Fish& fish = shole[j];

			fish.id = j;

			fish.x = fRand(-10, 10);
			fish.y = fRand(30, 45);
			fish.z = fRand(-10, 10);

			fish.d_x = fRand(-0.1, 0.1);
			fish.d_y = fRand(-0.1, 0.1);
			fish.d_z = fRand(-0.1, 0.1);
			fish.swimCycle = fRand(0, 7);

			fish.rot_x = rot_x;
			fish.rot_y = rot_y;
			fish.rot_z = rot_z;

			fish.ddx = 0;
			fish.ddy = 0;
			fish.ddz = 0;
		}
	}
}

void BoidsController::keepWithinBounds(int school_id, int id, Fish fish_list[][NUMBER_FISH]) {
	int margin = 3;
	double turnFactor = 0.025;

	if (fish_list[school_id][id].x < -20 + margin) {
		fish_list[school_id][id].d_x += turnFactor ;
	}
	if (fish_list[school_id][id].x > 20 - margin) {
		fish_list[school_id][id].d_x -= turnFactor;
	}
	if (fish_list[school_id][id].y < 0.0 + margin) { //HARD SURFICE
		fish_list[school_id][id].d_y += turnFactor;
	}
	if (fish_list[school_id][id].y > 20 - margin) {
		fish_list[school_id][id].d_y -= turnFactor;
	}
	if (fish_list[school_id][id].z < -20 + margin) {
		fish_list[school_id][id].d_z += turnFactor;
	}
	if (fish_list[school_id][id].z > 20 - margin) {
		fish_list[school_id][id].d_z -= turnFactor;
	}
}


void BoidsController::keepWithinBounds(Fish& fish) {
	double margin = 2;
	double turnFactor = 0.0100;

	if (fish.x < -30 + margin) {
		fish.d_x += turnFactor;
	}
	if (fish.x > 30 - margin) {
		fish.d_x -= turnFactor;
	}
	if (fish.y < 0.0 + margin) { //HARD SURFICE
		fish.d_y += turnFactor;
	}
	if (fish.y > 25 - margin) {
		fish.d_y -= turnFactor;
	}
	if (fish.z < -30 + margin) {
		fish.d_z += turnFactor;
	}
	if (fish.z > 30 - margin) {
		fish.d_z -= turnFactor;
	}


	bool close = false;
	/*
	for (int i = 0; i < obsticles.size(); i++) {
		//double dist = distance(fish, obsticles[i]);

		if ( abs(fish.x - obsticles[i].x) < margin) {
			close = true;
			if (fish.x > obsticles[i].x)	fish.d_x += 0.0025;
			else							fish.d_x -= 0.0025;
		}

		if (abs(fish.y - obsticles[i].y) < margin) {
			close = true;
			if (fish.y > obsticles[i].y)	fish.d_y += 0.0025;
			else							fish.d_y -= 0.0025;
		}

		if (abs(fish.z - obsticles[i].z) < margin) {
			close = true;
			if (fish.z > obsticles[i].z)	fish.d_z += 0.0025;
			else							fish.d_z -= 0.0025;
		}

		if (close) {
			return;
		}
	
	}*/
}

void BoidsController::flyTowardsCenter(int school_id, int id, int numBoids, Fish fish_list[][NUMBER_FISH]) {
	double centeringFactor = 0.001; // adjust velocity by this %

	double centerX = 0;
	double centerY = 0;
	double centerZ = 0;
	int numNeighbors = 0;

	for (int i = 0; i < NUMBER_FISH; i++) {
		if (distance(school_id, id, school_id, i, fish_list) < visualRange) {
			centerX += fish_list[school_id][i].x;
			centerY += fish_list[school_id][i].y;
			centerZ += fish_list[school_id][i].z;
			numNeighbors += 1;
		}
	}

	if (numNeighbors) {
		centerX = centerX / numNeighbors;
		centerY = centerY / numNeighbors;
		centerZ = centerZ / numNeighbors;

		fish_list[school_id][id].d_x += (centerX - fish_list[school_id][id].x) * centeringFactor;
		fish_list[school_id][id].d_y += (centerY - fish_list[school_id][id].y) * centeringFactor;
		fish_list[school_id][id].d_z += (centerZ - fish_list[school_id][id].z) * centeringFactor;
	}

}


void BoidsController::flyTowardsCenter(Fish& the_fish, Shoal shoal) {
	double centeringFactor = shoal.coherence; // adjust velocity by this %

	double centerX = 0;
	double centerY = 0;
	double centerZ = 0;
	int numNeighbors = 0;

	for (int i = 0; i < shoal.get().size(); i++) {

		Fish& fish = shoal.get()[i];

		if (distance(the_fish, fish) < shoal.visualRange) {
			centerX += fish.x;
			centerY += fish.y;
			centerZ += fish.z;
			numNeighbors += 1;
		}
	}

	if (numNeighbors) {
		centerX = centerX / numNeighbors;
		centerY = centerY / numNeighbors;
		centerZ = centerZ / numNeighbors;

		the_fish.d_x += (centerX - the_fish.x) * centeringFactor;
		the_fish.d_y += (centerY - the_fish.y) * centeringFactor;
		the_fish.d_z += (centerZ - the_fish.z) * centeringFactor;
	}

}


// Move away from other boids that are too close to avoid colliding
void BoidsController::avoidOthers(int school_id, int id, int numBoids, Fish fish_list[][NUMBER_FISH]) {
	int minDistance = 2; // The distance to stay away from other boids
	double avoidFactor = 0.0035; // Adjust velocity by this %
	double moveX = 0;
	double moveY = 0;
	double moveZ = 0;

	for (int i = 0; i < NUMBER_SCOALES; i++) {
		for (int j = 0; j < numBoids; j++) {
			double dist = distance(school_id, id, i, j, fish_list);
			if (dist != 0 && dist < minDistance) {
				moveX += (fish_list[school_id][id].x - fish_list[i][j].x) / (dist * dist);
				moveY += (fish_list[school_id][id].y - fish_list[i][j].y) / (dist * dist);
				moveZ += (fish_list[school_id][id].z - fish_list[i][j].z) / (dist * dist);
			}
		}

		fish_list[school_id][id].d_x += moveX * avoidFactor;
		fish_list[school_id][id].d_y += moveY * avoidFactor;
		fish_list[school_id][id].d_z += moveZ * avoidFactor;
	}
}

void BoidsController::avoidOthers(Fish& the_fish, std::vector <Shoal>& sholes) {
	double minDistance = 2; // The distance to stay away from other boids
	//double minDistance = separation;

	double avoidFactor; // Adjust velocity by this %
	double moveX = 0;
	double moveY = 0;
	double moveZ = 0;

	for (int i = 0; i < sholes.size(); i++) {

		avoidFactor = sholes[i].separation;

		std::vector<Fish>& fish = sholes[i].get();

		bound bounds = sholes[i].bounds;

		if (bounds.max_x + minDistance < the_fish.x) continue;
		if (bounds.min_x - minDistance > the_fish.x) continue;

		if (bounds.max_y + minDistance < the_fish.y) continue;
		if (bounds.min_y - minDistance > the_fish.y) continue;

		if (bounds.max_z + minDistance < the_fish.z) continue;
		if (bounds.min_z - minDistance > the_fish.z) continue;

		for (int j = 0; j < fish.size(); j++) {
			Fish& a_fish = fish[j];

			double dist = distance(the_fish, sholes[i].get()[j]);

			if (dist != 0 && dist < minDistance) {
				moveX += (the_fish.x - a_fish.x) / dist;
				moveY += (the_fish.y - a_fish.y) / dist;
				moveZ += (the_fish.z - a_fish.z) / dist;
			}
		}
		the_fish.d_x += moveX * avoidFactor;
		the_fish.d_y += moveY * avoidFactor;
		the_fish.d_z += moveZ * avoidFactor;
	}
}

void BoidsController::matchVelocity(int school_id, int id, int numBoids, Fish fish_list[][NUMBER_FISH]) {
	double matchingFactor = 0.01; // Adjust by this % of average velocity

	double avgDX = 0;
	double avgDY = 0;
	double avgDZ = 0;
	int numNeighbors = 0;

	for (int i = 0; i < numBoids; i++) {
		if (distance(school_id, id, school_id, i, fish_list) < visualRange) {
			avgDX += fish_list[school_id][i].d_x;
			avgDY += fish_list[school_id][i].d_y;
			avgDZ += fish_list[school_id][i].d_z;
			numNeighbors += 1;
		}
	}

	if (numNeighbors) {
		avgDX = avgDX / numNeighbors;
		avgDY = avgDY / numNeighbors;
		avgDZ = avgDZ / numNeighbors;

		fish_list[school_id][id].d_x += (avgDX - fish_list[school_id][id].d_x) * matchingFactor;
		fish_list[school_id][id].d_y += (avgDY - fish_list[school_id][id].d_y) * matchingFactor;
		fish_list[school_id][id].d_z += (avgDZ - fish_list[school_id][id].d_z) * matchingFactor;
	}
}

void BoidsController::matchVelocity(Fish& the_fish, Shoal shoal){
	double matchingFactor = shoal.alignment; // Adjust by this % of average velocity

	double avgDX = 0;
	double avgDY = 0;
	double avgDZ = 0;
	int numNeighbors = 0;

	for (int i = 0; i < shoal.get().size(); i++) {

		Fish& fish = shoal.get()[0];

		if (distance(the_fish, fish) < visualRange) {
			avgDX += fish.d_x;
			avgDY += fish.d_y;
			avgDZ += fish.d_z;
			numNeighbors += 1;
		}
	}

	if (numNeighbors) {
		avgDX = avgDX / numNeighbors;
		avgDY = avgDY / numNeighbors;
		avgDZ = avgDZ / numNeighbors;

		the_fish.d_x += (avgDX - the_fish.d_x) * matchingFactor;
		the_fish.d_y += (avgDY - the_fish.d_y) * matchingFactor;
		the_fish.d_z += (avgDZ - the_fish.d_z) * matchingFactor;
	}
}

void BoidsController::avoidObsticle(Fish& the_fish) {
	double minDistance = 4; // The distance to stay away from other boids
	double avoidFactor = 0.005; // Adjust velocity by this %
	double moveX = 0;
	double moveY = 0;
	double moveZ = 0;

	if (boundory.max_x + minDistance < the_fish.x) return;
	if (boundory.min_x - minDistance > the_fish.x) return;

	if (boundory.max_y + minDistance < the_fish.y) return;
	if (boundory.min_y - minDistance > the_fish.y) return;

	if (boundory.max_z + minDistance < the_fish.z) return;
	if (boundory.min_z - minDistance > the_fish.z) return;

	for (int i = 0; i < obsticles.size(); i++) {
		double dist = distance(the_fish, obsticles[i]);

		if (dist != 0 && dist < minDistance) {
			moveX += (the_fish.x - obsticles[i].x) / dist;
			moveY += (the_fish.y - obsticles[i].y) / dist;
			moveZ += (the_fish.z - obsticles[i].z) / dist;
		}
	}

	the_fish.d_x += moveX * avoidFactor;
	the_fish.d_y += moveY * avoidFactor;
	the_fish.d_z += moveZ * avoidFactor;
}

void BoidsController::limitSpeed(int school_id, int id, int numBoids, Fish fish_list[][NUMBER_FISH]) {
	double speedLimit = 0.05;

	double speed = sqrt(
		fish_list[school_id][id].d_x * fish_list[school_id][id].d_x + 
		fish_list[school_id][id].d_y * fish_list[school_id][id].d_y + 
		fish_list[school_id][id].d_z * fish_list[school_id][id].d_z
	);

	if (speed > speedLimit) {
		fish_list[school_id][id].d_x = (fish_list[school_id][id].d_x / speed) * speedLimit;
		fish_list[school_id][id].d_y = (fish_list[school_id][id].d_y / speed) * speedLimit;
		fish_list[school_id][id].d_z = (fish_list[school_id][id].d_z / speed) * speedLimit;
	}
}


void BoidsController::limitSpeed(Fish& fish) {
	double speedLimit = 0.20;

	double speed = sqrt(
		fish.d_x * fish.d_x +
		fish.d_y * fish.d_y +
		fish.d_z * fish.d_z
	);

	if (speed > speedLimit) {
		fish.d_x = (fish.d_x / speed) * speedLimit;
		fish.d_y = (fish.d_y / speed) * speedLimit;
		fish.d_z = (fish.d_z / speed) * speedLimit;
	}
}

void BoidsController::update(int numBoids, Fish fish_list[][NUMBER_FISH]) {
	// Update each boid
	for (int i = 0; i < NUMBER_SCOALES; i++) {
		for (int j = 0; j < numBoids; j++) {
			// Update the velocities according to each rule

			flyTowardsCenter(i, j,	numBoids, fish_list);
			avoidOthers(i, j,		numBoids, fish_list);
			matchVelocity(i, j,		numBoids, fish_list);
			limitSpeed(i, j,		numBoids, fish_list);
			keepWithinBounds(i, j,			  fish_list);

			// Update the position based on the current velocity
			fish_list[i][j].x += fish_list[i][j].d_x;
			fish_list[i][j].y += fish_list[i][j].d_y;
			fish_list[i][j].z += fish_list[i][j].d_z;
		}
	}
}

void BoidsController::update(std::vector<Shoal>& sholes) {
	// Update each boid

	std::vector<bound> shole_bounds = std::vector<bound>();


	for (int i = 0; i < sholes.size(); i++) {

		std::vector <Fish>& shole = sholes[i].get();

		for (int j = 0; j < shole.size(); j++) {
			// Update the velocities according to each rule
			Fish& fish = shole[j];

			flyTowardsCenter(fish, sholes[i]);
			avoidOthers(fish, sholes);
			matchVelocity(fish, sholes[i]);
			limitSpeed(fish);
			keepWithinBounds(fish);
			avoidObsticle(fish);

			// Update the position based on the current velocity
			double a_x = fish.ddx - fish.d_x;
			double a_y = fish.ddy - fish.d_y;
			double a_z = fish.ddz - fish.d_z;

			fish.ddx = fish.d_x;
			fish.ddy = fish.d_y;
			fish.ddz = fish.d_z;

			fish.x += fish.d_x;
			fish.y += fish.d_y;
			fish.z += fish.d_z;


			fish.swimCycle += sqrt(fish.d_x * fish.d_x + fish.d_y * fish.d_y + fish.d_z * fish.d_z) * 5;
		}

		sholes[i].calcBound();
	}
}

void BoidsController::setCoherence(double newCoherence) {
	BoidsController::coherence = newCoherence;
}
void BoidsController::setSeparation(double newSeparation) {
	BoidsController::separation = newSeparation;
}
void BoidsController::setAlignment(double newAlignment){
	BoidsController::alignment = newAlignment;
}
void BoidsController::setVisualRange(double newVisualRange){
	BoidsController::visualRange = newVisualRange;
}


void BoidsController::incrementCoherence() {

}
void BoidsController::decrementCoherence() {

}

void BoidsController::incrementSeparation() {

}
void BoidsController::decrementSeparation() {

}

void BoidsController::incrementAlignment() {

}
void BoidsController::decrementAlignment() {

}

void BoidsController::incrementVisualRange() {
	BoidsController::visualRange = BoidsController::visualRange * 2;

	if (BoidsController::visualRange > 38.4) {
		BoidsController::visualRange = 38.4;
	}
	printf("Visual Range %f\n", BoidsController::visualRange);

}
void BoidsController::decrementVisualRange() {
	BoidsController::visualRange = BoidsController::visualRange / 2;

	if (BoidsController::visualRange < 0.225) {
		BoidsController::visualRange = 0.225;
	}
	printf("Visual Range %f\n", BoidsController::visualRange);
}

void BoidsController::addObsticle(glm::vec3 obsticle) {
	BoidsController::obsticles.push_back(obsticle);

	printf("added: <%f, %f, %f>\n", obsticle.x, obsticle.y, obsticle.z);
}

void BoidsController::calcBound() {
	double max_x = obsticles[0].x;
	double min_x = obsticles[0].x;

	double max_y = obsticles[0].y;
	double min_y = obsticles[0].y;

	double max_z = obsticles[0].z;
	double min_z = obsticles[0].z;

	for (int i = 0; i < obsticles.size(); i++) {
		if (obsticles[i].x > max_x) max_x = obsticles[i].x;
		if (obsticles[i].x < min_x) min_x = obsticles[i].x;

		if (obsticles[i].y > max_y) max_y = obsticles[i].y;
		if (obsticles[i].y < min_y) min_y = obsticles[i].y;

		if (obsticles[i].z > max_z) max_z = obsticles[i].z;
		if (obsticles[i].z < min_z) min_z = obsticles[i].z;
	}

	BoidsController::boundory.max_x = max_x;
	BoidsController::boundory.min_x = min_x;

	BoidsController::boundory.max_y = max_y;
	BoidsController::boundory.min_y = min_y;

	BoidsController::boundory.max_z = max_z;
	BoidsController::boundory.min_z = min_z;
}

bound BoidsController::getBound() {
	return BoidsController::boundory;
}