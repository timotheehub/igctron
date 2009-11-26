/*
 * Player.cpp
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#include "Player.h"
#include "Vehicle.h"
using namespace std;
using namespace Utils;

void Player::Init()
{
	myVehicle.Init();
}

void Player::Update()
{
	myVehicle.MoveForward();
	//Displayer::???;
}

void Player::MoveLeft()
{
	myVehicle.MoveLeft();
}

void Player::MoveRight()
{
	myVehicle.MoveRight();
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

Player::Player(string aName, CartesianVector initPos, CartesianVector initSpeed) :
	name(aName), myVehicle(initPos, initSpeed)
{

}
