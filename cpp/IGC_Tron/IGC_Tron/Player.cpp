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
	if (isAlive)
	{
		myVehicle.MoveForward(dt);
		myWall.SetLastVertex(myVehicle.GetPosition());
	}
	else if (!OPTION_WALL_AFTER_DEATH)
	{
		myWall.Collapse(dt);
	}
}

void Player::MoveLeft()
{
	if (isAlive)
	{
		myVehicle.MoveLeft();
		myWall.AddVertex();
	}
}

void Player::MoveRight()
{
	if (isAlive)
	{
		myVehicle.MoveRight();
		myWall.AddVertex();
	}
}

void Player::Boost()
{
	if (isAlive)
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
	if (!isAlive)
	{
		return false;
	}
	else
	{
		Utils::Rectangle r = myVehicle.GetRectangle();
		isAlive = !(r.IsOutOf(Game::GetInstance()->GetPlane()) || (&killer
				!= this && r.IsInCollision(killer.myVehicle.GetRectangle()))
				|| killer.myWall.IsInCollision(r));

		return !isAlive;
	}
}

/******************************************************************************
 *                                Affichage                                    *
 ******************************************************************************/
void Player::Draw() const
{
	if (isAlive)
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
			initSpeed, WALL_BASE_HEIGHT), initPosition(initPos), isAlive(true), playerNumber(
			aNumber)
{

}
