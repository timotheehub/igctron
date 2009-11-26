/*
 * Vehicle.cpp
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#include "Vehicle.h"
#include "Globals.h"
#include "Displayer.h"

using namespace Utils;

const double Vehicle::BOOST_COEF = 2.0;
const double Vehicle::BOOST_LENGTH = 5.0;

void Vehicle::Init()
{
	position = initPosition;
	speed = initSpeed;
	boost = false;
}

void Vehicle::MoveForward()
{
	if (boost && (Displayer::GetTime() - boostBeginDate) >= BOOST_LENGTH)
	{
		boost = false;
	}

	if (boost)
	{
		position += BOOST_COEF * speed;
	}
	else
	{
		position += speed;
	}
}

void Vehicle::Boost()
{
	boostBeginDate = Displayer::GetTime();
	boost = true;
}

void Vehicle::MoveLeft()
{
	double tmp = speed.x;
	speed.x = speed.y;
	speed.y = -tmp;
}
void Vehicle::MoveRight()
{
	double tmp = speed.x;
	speed.x = -speed.y;
	speed.y = tmp;
}

CartesianVector Vehicle::GetPosition() const
{
	return position;
}

Vehicle::Vehicle(CartesianVector anInitPosition, CartesianVector anInitSpeed) :
	initPosition(anInitPosition), initSpeed(anInitSpeed), position(
			anInitPosition), speed(anInitSpeed), boostBeginDate(0)
{

}
