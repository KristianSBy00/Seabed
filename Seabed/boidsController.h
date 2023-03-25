#pragma once
#ifndef BOIDS_CONTROLLER_CLASS_H
#define BOIDS_CONTROLLER_CLASS_H

#include "Fish.h"


class BoidsController
{
public:
	double visualRange = 5;
	BoidsController(double visualRange);
	BoidsController();

	double fRand(double fMin, double fMax);
	double distance(int school_id_1, int id_1, int school_id2, int id_2, Fish fish_list[][200]);
	void initBoids(double rot_x, double rot_y, double rot_z, int numBoids, Fish fish_list[][200]);
	void keepWithinBounds(int school_id, int id, Fish fish_list[][200]);
	void flyTowardsCenter(int school_id, int id, int numBoids, Fish fish_list[][200]);
	void avoidOthers(int school_id, int id, int numBoids, Fish fish_list[][200]);
	void matchVelocity(int school_id, int id, int numBoids, Fish fish_list[][200]);
	void limitSpeed(int school_id, int id, int numBoids, Fish fish_list[][200]);
	void update(int numBoids, Fish fish_list[][200]);
};
#endif