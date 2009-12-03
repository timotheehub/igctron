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

	void MoveForward(double dt);
	void Boost();
	void MoveLeft();
	void MoveRight();

	void Draw() const;
	void Explode() const;

	Vehicle(Utils::CartesianVector anInitPosition,
			Utils::CartesianVector anInitSpeed, int aNumero);

	Utils::CartesianVector GetPosition() const;
	Utils::Rectangle GetRectangle() const;

protected:
	static const double BOOST_COEF;
	static const double BOOST_LENGTH;

	Utils::CartesianVector initPosition;
	Utils::CartesianVector initSpeed;
	Utils::CartesianVector position;
	Utils::CartesianVector speed;
	bool boost;
	double boostBeginDate;
	int numeroPlayer;
};

#endif /* VEHICLE_H_ */
