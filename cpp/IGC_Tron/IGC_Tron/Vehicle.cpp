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

const double Vehicle::RECTANGLE_GAP = 10e-5;
const double Vehicle::BOOST_COEF = 2.0;
const double Vehicle::BOOST_LENGTH = 5.0;

/******************************************************************************
 *                              Mise � jour                                    *
 ******************************************************************************/
void Vehicle::Init(const CartesianVector& initPosition)
{
	position = initPosition;
	speed = initSpeed;
	boost = false;
}

void Vehicle::MoveForward(double dt)
{
	if (boost)
	{
		boostElapsed += dt;
		if (boostElapsed >= BOOST_LENGTH)
		{
			boost = false;
		}
		position += BOOST_COEF * dt * speed;
	}
	else
	{
		position += dt * speed;
	}
}

void Vehicle::Boost()
{
	boostElapsed = 0.0;
	boost = true;
}

void Vehicle::MoveLeft()
{
	double tmp = speed.x;
	speed.x = -speed.z;
	speed.z = tmp;
}
void Vehicle::MoveRight()
{
	double tmp = speed.x;
	speed.x = speed.z;
	speed.z = -tmp;
}

CartesianVector Vehicle::GetPosition() const
{
	return position;
}

Utils::Rectangle Vehicle::GetRectangle() const
{
	return Utils::Rectangle(position, speed, 4.0, RECTANGLE_GAP, 1.8, 1.8);
}

/******************************************************************************
 *                                Affichage                                    *
 ******************************************************************************/
void Vehicle::Draw() const
{
	Displayer *aDisplayer = Displayer::GetInstance();
	IGC::Renderer *renderer = aDisplayer->GetRenderer();
	IGC::Factory *factory = aDisplayer->GetFactory();

	IGC::Model* model;
	switch (playerNumber)
	{
	case 0:
		model = factory->acquire((IGC::Model*) NULL, "model_ship1");
		break;
	case 1:
		model = factory->acquire((IGC::Model*) NULL, "model_ship2");
		break;
	case 2:
		model = factory->acquire((IGC::Model*) NULL, "model_ship3");
		break;
	case 3:
		model = factory->acquire((IGC::Model*) NULL, "model_ship4");
		break;
	default:
		model = factory->acquire((IGC::Model*) NULL, "model_ship1");
		break;
	}
	model->setCenter(position.x - 10, position.y + 1, position.z - 15);
	if (abs(speed.x) > abs(speed.z))
	{
		if (speed.x < 0)
			model->setAngle(PI / 2, PI / 2, 0);
		else
			model->setAngle(PI / 2, 3 * PI / 2, 0);
	}
	else
	{
		if (speed.z < 0)
			model->setAngle(PI / 2, 0, 0);
		else
			model->setAngle(PI / 2, PI, 0);
	}

	IGC::Texture* texture = factory->acquire((IGC::Texture*) NULL,
			"back_screen_menu");
	texture->bind();
	renderer->setTransparency(false);
	model->render();
}

void Vehicle::Explode() const
{

}

/******************************************************************************
 *                 Constructeurs et destructeurs                               *
 ******************************************************************************/
Vehicle::Vehicle(CartesianVector anInitPosition, CartesianVector anInitSpeed,
		int aNumber) :
	initSpeed(anInitSpeed), position(anInitPosition), speed(anInitSpeed),
			boostElapsed(0.0), playerNumber(aNumber)
{

}
