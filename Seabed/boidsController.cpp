#include"boidsController.h"
#include <cmath>


BoidsController::BoidsController(double visualRange = 5.0) {
	BoidsController::visualRange = visualRange;
}

BoidsController::BoidsController() {
	BoidsController::visualRange = 5.0;
}

double BoidsController::fRand(double fMin, double fMax) {
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}


double BoidsController::distance(int school_id_1, int id_1, int school_id_2, int id_2, Fish fish_list[][100]) {
	return sqrt(
		(fish_list[school_id_1][id_1].x - fish_list[school_id_2][id_2].x) * (fish_list[school_id_1][id_1].x - fish_list[school_id_2][id_2].x) +
		(fish_list[school_id_1][id_1].y - fish_list[school_id_2][id_2].y) * (fish_list[school_id_1][id_1].y - fish_list[school_id_2][id_2].y) +
		(fish_list[school_id_1][id_1].z - fish_list[school_id_2][id_2].z) * (fish_list[school_id_1][id_1].z - fish_list[school_id_2][id_2].z)
	);
}


void BoidsController::initBoids(double rot_x, double rot_y, double rot_z, int numBoids, Fish fish_list[][100]) {

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < numBoids; j++) {
			fish_list[i][j].id = i;

			fish_list[i][j].x = fRand(-10, 10);
			fish_list[i][j].y = fRand(0.5, 15);
			fish_list[i][j].z = fRand(-10, 10);;

			fish_list[i][j].d_x = fRand(-0.1, 0.1);
			fish_list[i][j].d_y = fRand(-0.1, 0.1);
			fish_list[i][j].d_z = fRand(-0.1, 0.1);

			fish_list[i][j].rot_x = rot_x;
			fish_list[i][j].rot_y = rot_y;
			fish_list[i][j].rot_z = rot_z;
		}
	}
}

void BoidsController::keepWithinBounds(int school_id, int id, Fish fish_list[][100]) {
	int margin = 1;
	double turnFactor = 0.005;

	if (fish_list[school_id][id].x < -10 + margin) {
		fish_list[school_id][id].d_x += turnFactor ;
	}
	if (fish_list[school_id][id].x > 10 - margin) {
		fish_list[school_id][id].d_x -= turnFactor;
	}
	if (fish_list[school_id][id].y < 0.0 + margin) { //HARD SURFICE
		fish_list[school_id][id].d_y += turnFactor;
	}
	if (fish_list[school_id][id].y > 15 - margin) {
		fish_list[school_id][id].d_y -= turnFactor;
	}
	if (fish_list[school_id][id].z < -10 + margin) {
		fish_list[school_id][id].d_z += turnFactor;
	}
	if (fish_list[school_id][id].z > 10 - margin) {
		fish_list[school_id][id].d_z -= turnFactor;
	}
}


void BoidsController::flyTowardsCenter(int school_id, int id, int numBoids, Fish fish_list[][100]) {
	double centeringFactor = 0.0005; // adjust velocity by this %

	double centerX = 0;
	double centerY = 0;
	double centerZ = 0;
	int numNeighbors = 0;

	for (int i = 0; i < numBoids; i++) {
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


// Move away from other boids that are too close to avoid colliding
void BoidsController::avoidOthers(int school_id, int id, int numBoids, Fish fish_list[][100]) {
	int minDistance = 3; // The distance to stay away from other boids
	double avoidFactor = 0.0005; // Adjust velocity by this %
	double moveX = 0;
	double moveY = 0;
	double moveZ = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < numBoids; j++) {

			if (fish_list[i][j].id != fish_list[school_id][id].id) {
				double dist = distance(school_id, id, i, j, fish_list);
				if (dist < minDistance) {
					moveX += (fish_list[school_id][id].x - fish_list[j][i].x) / (dist * dist);
					moveY += (fish_list[school_id][id].y - fish_list[j][i].y) / (dist * dist);
					moveZ += (fish_list[school_id][id].z - fish_list[j][i].z) / (dist * dist);
				}
			}
		}

		fish_list[school_id][id].d_x += moveX * avoidFactor;
		fish_list[school_id][id].d_y += moveY * avoidFactor;
		fish_list[school_id][id].d_z += moveZ * avoidFactor;
	}
}

void BoidsController::matchVelocity(int school_id, int id, int numBoids, Fish fish_list[][100]) {
	double matchingFactor = 0.005; // Adjust by this % of average velocity

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

void BoidsController::limitSpeed(int school_id, int id, int numBoids, Fish fish_list[][100]) {
	double speedLimit = 0.5;

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


void BoidsController::update(int numBoids, Fish fish_list[][100]) {
	// Update each boid
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < numBoids; j++) {
			// Update the velocities according to each rule

			//fish boid = fish_list[i];
			flyTowardsCenter(i, j, numBoids, fish_list);
			avoidOthers(i, j, numBoids, fish_list);
			matchVelocity(i, j, numBoids, fish_list);
			limitSpeed(i, j, numBoids, fish_list);
			keepWithinBounds(i, j, fish_list);

			// Update the position based on the current velocity
			fish_list[i][j].x += fish_list[i][j].d_x;
			fish_list[i][j].y += fish_list[i][j].d_y;
			fish_list[i][j].z += fish_list[i][j].d_z;
		}
	}
}