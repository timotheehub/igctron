/*
 * Player.cpp
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#include "Player.h"
#include "Vehicle.h"
#include "Game.h"
using namespace std;
using namespace Utils;

// TODO : convertir en variables
const bool Player::OPTION_WALL_AFTER_DEATH = false;
const float Player::WALL_BASE_HEIGHT = 1.0;

/******************************************************************************
 *                             Mise a jour                                     *
 ******************************************************************************/
void Player::Init()
{
	myVehicle.Init(initPosition);
	myWall.Init(initPosition);
}

void Player::Update(double dt)
{

	if (IsAlive())
	{
		myVehicle.MoveForward(dt);
		myWall.SetLastVertex(myVehicle.GetPosition());
	}
	else
	{
		if (status == DYING)
		{
			status = DEAD;
		}
		if (!OPTION_WALL_AFTER_DEATH)
		{
			myWall.Collapse(dt);
		}
	}
}

void Player::MoveLeft()
{
	if (IsAlive())
	{
		myVehicle.MoveLeft();
		myWall.AddVertex();
	}
}

void Player::MoveRight()
{
	if (IsAlive())
	{
		myVehicle.MoveRight();
		myWall.AddVertex();
	}
}

void Player::Boost()
{
	if (IsAlive())
	{
		myVehicle.Boost();
	}
}

CartesianVector Player::GetPosition() const
{
	return myVehicle.GetPosition();
}

string Player::GetName() const
{
	return name;
}

bool Player::IsGettingKilled(const Player& killer)
{
	if (!IsAlive())
	{
		return false;
	}
	else
	{
		Utils::Rectangle r = myVehicle.GetRectangle();
		if (
				r.IsOutOf(Game::GetInstance()->GetPlane()) ||
					(
						&killer != this && killer.status != DEAD &&
						r.IsInCollision(killer.myVehicle.GetRectangle())
					)
					|| killer.myWall.IsInCollision(r)
			)
		{
			// Le joueur va mourir
			status = DYING;
		}

		return !IsAlive();
	}
}

/******************************************************************************
 *                                Affichage                                    *
 ******************************************************************************/
void Player::Draw() const
{
	if (IsAlive())
	{
		myVehicle.Draw();
	}
	myWall.Draw();
}

/******************************************************************************
 *                 Constructeurs et destructeurs                               *
 ******************************************************************************/

Player::Player(string aName, CartesianVector initPos,
		CartesianVector initSpeed, int aNumber) :
	name(aName), myVehicle(initPos, initSpeed, aNumber), myWall(initPos,
			initSpeed, WALL_BASE_HEIGHT), initPosition(initPos), 
			playerNumber(aNumber),status(LIVING)
{

}
