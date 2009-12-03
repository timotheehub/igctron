/*
 * Player.h
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include "Globals.h"
#include "Vehicle.h"

class Player
{
public:
	void Init();

	void Update();
	void MoveLeft();
	void MoveRight();
	void Boost();

	void Draw ( );

	Utils::CartesianVector GetPosition() const;
	std::string GetName() const;

	Player(std::string aName, Utils::CartesianVector initPos,
			Utils::CartesianVector initSpeed);

private:
	std::string name;
	Vehicle myVehicle;
	bool isAlive;
};

#endif /* PLAYER_H_ */
