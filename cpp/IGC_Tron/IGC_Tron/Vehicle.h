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
	void Init();

	void MoveForward();
	void Boost();
	void MoveLeft();
	void MoveRight();

	void Draw ( );

	Vehicle(Utils::CartesianVector anInitPosition,
			Utils::CartesianVector anInitSpeed);

	Utils::CartesianVector GetPosition() const;

protected:
	static const double BOOST_COEF;
	static const double BOOST_LENGTH;

	Utils::CartesianVector initPosition;
	Utils::CartesianVector initSpeed;
	Utils::CartesianVector position;
	Utils::CartesianVector speed;
	bool boost;
	double boostBeginDate;
};

#endif /* VEHICLE_H_ */
