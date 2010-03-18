/*
 * Vehicle.h
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <string>

#include "Globals.h"
#include "Common.h"

class Vehicle
{
public:
	static const float HEIGHT;

	void Init(const Utils::CartesianVector& initPosition,
			const Utils::CartesianVector& initSpeed,
			const std::string& modelName, float4 color);

	void MoveForward(double dt);
	void Boost();
	void MoveLeft();
	void MoveRight();

	void Draw() const;
	void Explode() const;

	Vehicle ( );
	virtual ~Vehicle ( );

	Utils::CartesianVector GetPosition() const;
	Utils::CartesianVector GetSpeed() const;
	Utils::Rectangle GetRectangle() const;

protected:
	static const double RECTANGLE_GAP;
	static const double BOOST_COEF;
	static const double BOOST_LENGTH;

	Utils::CartesianVector position;
	Utils::CartesianVector speed;
	bool boost;
	double boostElapsed;

	IGC::Model* model;

	float length;
	float width;
	//float height; // TODO : utile ?
};

#endif /* VEHICLE_H_ */
