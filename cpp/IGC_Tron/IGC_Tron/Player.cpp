/*
 * Player.cpp
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#include "Player.h"
#include "Vehicle.h"
#include <iostream>
using namespace std;
using namespace Utils;

/******************************************************************************
*                             Mise a jour                                     *
******************************************************************************/
void Player::Init()
{
	myVehicle.Init();
}

void Player::Update(double dt)
{
	myVehicle.MoveForward(dt);
	myWall.SetLastVertex(myVehicle.GetPosition());
}

void Player::MoveLeft()
{
	myVehicle.MoveLeft();
	myWall.NewVertex();
}

void Player::MoveRight()
{
	myVehicle.MoveRight();
	myWall.NewVertex();
}

void Player::Boost()
{
	myVehicle.Boost();
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
		Rectangle r = myVehicle.GetRectangle();
		isAlive = r.IsInCollision(killer.myVehicle.GetRectangle())
				|| killer.myWall.IsInCollision(r);
		if (!isAlive)
		{
			myVehicle.Explode();
			return true;
		}
		else
		{
			return false;
		}
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
}

/******************************************************************************
 *                 Constructeurs et destructeurs                               *
 ******************************************************************************/

Player::Player(string aName, CartesianVector initPos, CartesianVector initSpeed, int aNumero) :
	name(aName), myVehicle(initPos, initSpeed, aNumero), isAlive(true), myWall(initPos)
{

}
