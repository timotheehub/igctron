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
const float Vehicle::LENGTH = 1.0f;
const float Vehicle::WIDTH = 0.5f;
const float Vehicle::HEIGHT = 0.0f;

/*******************************************************************************
 *                              Mise a jour                                    *
 ******************************************************************************/
void Vehicle::Init(const Utils::CartesianVector& initPosition)
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

CartesianVector Vehicle::GetSpeed() const
{
	return speed;
}

Utils::Rectangle Vehicle::GetRectangle() const
{
	return Utils::Rectangle(position, speed, length, RECTANGLE_GAP, width / 2,
			width / 2);
}

IGC::Model* Vehicle::getModel () const
{
	IGC::Factory *factory = Displayer::GetInstance()->GetFactory();
	IGC::Model* model;
	// TODO : stocker le Model*
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

	return model;
}

void Vehicle::updateSize ()
{
	//float3 f = getModel()->getMesh()->getBoundingBox().max;

	//printf("x : %f, y : %f, z : %f",f.x,f.y,f.z);
	length = LENGTH;
	width = WIDTH;
}

/******************************************************************************
 *                                Affichage                                    *
 ******************************************************************************/
void Vehicle::Draw() const
{
	Displayer* aDisplayer = Displayer::GetInstance();
	Renderer* renderer = aDisplayer->GetRenderer();
	IGC::Factory *factory = aDisplayer->GetFactory();

	IGC::Model* model = getModel();

	if (abs(speed.x) > abs(speed.z))
	{
		if (speed.x < 0.0)
		{
			model->setAngle(- PI / 2.0f, PI / 2.0f, 0.0f);
			model->setCenter(position.x - (length / 2 + RECTANGLE_GAP),
					position.y + HEIGHT, position.z);
		}
		else
		{
			model->setAngle(- PI / 2.0f, 3.0f * PI / 2.0f, 0.0f);
			model->setCenter(position.x + (length / 2.0 + RECTANGLE_GAP),
					position.y + HEIGHT, position.z);
		}
	}
	else
	{
		if (speed.z < 0.0f)
		{
			model->setAngle(- PI / 2.0f, 0.0f, 0.0f);
			model->setCenter(position.x, position.y + HEIGHT, position.z
					- (length / 2.0f + RECTANGLE_GAP));
		}
		else
		{
			model->setAngle(- PI / 2.0f, PI, 0.0f);
			model->setCenter(position.x, position.y + HEIGHT, position.z
					+ (length / 2.0f + RECTANGLE_GAP));
		}
	}
	IGC::Texture* texture = factory->acquire((IGC::Texture*) NULL,
			"back_screen_menu");
	texture->unbind ( );
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
			boost(false), boostElapsed(0.0), playerNumber(aNumber)
{
	updateSize ();
}
