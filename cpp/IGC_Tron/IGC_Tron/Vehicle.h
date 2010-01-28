/*
 * Vehicle.h
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "Globals.h"

class Vehicle
{
public:
    static const float LENGTH;
	static const float WIDTH;
	static const float HEIGHT;

	void Init(const Utils::CartesianVector& initPosition);

	void MoveForward(double dt);
	void Boost();
	void MoveLeft();
	void MoveRight();

	void Draw() const;
	void Explode() const;

	Vehicle(Utils::CartesianVector anInitPosition,
			Utils::CartesianVector anInitSpeed, int aNumber);

	Utils::CartesianVector GetPosition() const;
	Utils::CartesianVector GetSpeed() const;
	Utils::Rectangle GetRectangle() const;

protected:
	static const double RECTANGLE_GAP;
	static const double BOOST_COEF;
	static const double BOOST_LENGTH;

	Utils::CartesianVector initSpeed;
	Utils::CartesianVector position;
	Utils::CartesianVector speed;
	bool boost;
	double boostElapsed;
	int playerNumber;
};

#endif /* VEHICLE_H_ */
