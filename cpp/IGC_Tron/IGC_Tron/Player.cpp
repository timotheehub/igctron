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

/******************************************************************************
*                             Mise à jour                                     *
******************************************************************************/
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

/******************************************************************************
*                                Affichage                                    *
******************************************************************************/
void Player::Draw ( )
{
	if ( isAlive )
	{
		myVehicle.Draw ( );
	}
}

/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************/
Player::Player(string aName, CartesianVector initPos, CartesianVector initSpeed, int aNumero) :
	name(aName), myVehicle(initPos, initSpeed,aNumero), isAlive(true), numeroPlayer ( aNumero )
{

}
