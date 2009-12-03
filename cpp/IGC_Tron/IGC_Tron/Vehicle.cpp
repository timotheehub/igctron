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

/******************************************************************************
*                              Mise à jour                                    *
******************************************************************************/
void Vehicle::Init()
{
	position = initPosition;
	speed = initSpeed;
	boost = false;
}

void Vehicle::MoveForward()
{
	if (boost && (Displayer::GetInstance()->GetTime() - boostBeginDate) >= BOOST_LENGTH)
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
	boostBeginDate = Displayer::GetInstance()->GetTime();
	boost = true;
}

void Vehicle::MoveLeft()
{
	double tmp = speed.z;
	speed.z = -speed.x;
	speed.x = tmp;
}
void Vehicle::MoveRight()
{
	double tmp = speed.z;
	speed.z = speed.x;
	speed.x = -tmp;
}

CartesianVector Vehicle::GetPosition() const
{
	return position;
}

/******************************************************************************
*                                Affichage                                    *
******************************************************************************/
void Vehicle::Draw ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Renderer *renderer = aDisplayer->GetRenderer ( );
	IGC::Factory *factory = aDisplayer->GetFactory ( );

	IGC::Model* model = factory->acquire( (IGC::Model*)NULL, "model_ship" );
	IGC::Texture* texture = factory->acquire( (IGC::Texture*)NULL, "back_screen_menu" );
	texture->bind();
	renderer->setTransparency( false );
	model->render();
}

/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************/
Vehicle::Vehicle(CartesianVector anInitPosition, CartesianVector anInitSpeed) :
	initPosition(anInitPosition), initSpeed(anInitSpeed), position(
			anInitPosition), speed(anInitSpeed), boostBeginDate(0)
{

}
