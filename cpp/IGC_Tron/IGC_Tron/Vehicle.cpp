/*
 * Vehicle.cpp
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#include "Settings.h"
#include "Vehicle.h"
#include "Globals.h"
#include "Displayer.h"

using namespace Utils;

const double Vehicle::RECTANGLE_GAP = 10e-5;
const float Vehicle::HEIGHT = 0.0f; // TODO : utile ?

/*******************************************************************************
 *                              Mise a jour                                    *
 ******************************************************************************/
void Vehicle::Init(const Utils::CartesianVector& initPosition,
		const Utils::CartesianVector& initSpeed,
		const std::string& modelName, float4 color)
{
	IGC::Factory* factory = Displayer::GetInstance()->GetFactory();
	BoundingBox bb;

	position = initPosition;
	speed = initSpeed;
	boost = false;

	Model* original = factory->acquire((IGC::Model*) NULL, modelName.c_str());
	model->Clone(original);
	factory->release(original);
	// TODO : coloriser

	bb = model->getBoundingBox();

	length = bb.max.z - bb.min.z;
	width = bb.max.x - bb.min.x;
}

void Vehicle::MoveForward(double dt)
{
	if (boost)
	{
		const GlobalSettings* settings = Settings::GetInstance()->GetGlobalSettings();
		boostElapsed += dt;
		if (boostElapsed >= settings->BoostLength)
		{
			boost = false;
		}
		position += settings->BoostCoef * dt * speed;
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

float Vehicle::GetLength() const
{
	return length;
}

float Vehicle::GetWidth() const
{
	return width;
}

/******************************************************************************
 *                                Affichage                                    *
 ******************************************************************************/
void Vehicle::Draw() const
{
	Displayer* aDisplayer = Displayer::GetInstance();
	Renderer* renderer = aDisplayer->GetRenderer();
	IGC::Factory *factory = aDisplayer->GetFactory();

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

	factory->release( texture );
}

void Vehicle::Explode() const
{

}

/******************************************************************************
 *                 Constructeurs et destructeurs                               *
 ******************************************************************************/
Vehicle::Vehicle ( ) :
	boost(false), boostElapsed(0.0)
{
	IGC::Factory *factory = Displayer::GetInstance()->GetFactory();

	model = factory->acquire((IGC::Model*) NULL);
}

Vehicle::~Vehicle ()
{
	IGC::Factory *factory = Displayer::GetInstance()->GetFactory();

	factory->release ( model );
}
