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
#include "Wall.h"

class Player
{
public:
	void Init();

	void Update(double dt);
	void MoveLeft();
	void MoveRight();
	void Boost();

	void Draw ( ) const;

	Utils::CartesianVector GetPosition() const;
	std::string GetName() const;
	bool IsGettingKilled(const Player& killer);
	// Provoque l'explosion en cas de mort

	Player(std::string aName, Utils::CartesianVector initPos,
			Utils::CartesianVector initSpeed, int aNumero);

private:
	std::string name;
	Vehicle myVehicle;
	Wall myWall;
	bool isAlive;
	int numeroPlayer;
};

#endif /* PLAYER_H_ */
