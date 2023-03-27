#pragma once
#ifndef BOIDS_CONTROLLER_CLASS_H
#define BOIDS_CONTROLLER_CLASS_H

#include"Fish.h"
#include<vector>
#include"Shoal.h"

#define NUMBER_SCOALES 3
#define NUMBER_FISH 150


class BoidsController
{
public:
	double visualRange = 5;
	BoidsController(double visualRange);
	BoidsController();

	double fRand(double fMin, double fMax);
	double distance(int school_id_1, int id_1, int school_id2, int id_2, Fish fish_list[][NUMBER_FISH]);
	void initBoids(double rot_x, double rot_y, double rot_z, int numBoids, Fish fish_list[][NUMBER_FISH]);
	void initBoids(double rot_x, double rot_y, double rot_z, std::vector<Shoal>& sholes);
	void keepWithinBounds(int school_id, int id, Fish fish_list[][NUMBER_FISH]);
	void keepWithinBounds(int school_id, int id, std::vector<Shoal> sholes);
	void flyTowardsCenter(int school_id, int id, int numBoids, Fish fish_list[][NUMBER_FISH]);
	void avoidOthers(int school_id, int id, int numBoids, Fish fish_list[][NUMBER_FISH]);
	void matchVelocity(int school_id, int id, int numBoids, Fish fish_list[][NUMBER_FISH]);
	void limitSpeed(int school_id, int id, int numBoids, Fish fish_list[][NUMBER_FISH]);
	void update(int numBoids, Fish fish_list[][NUMBER_FISH]);
};
#endif