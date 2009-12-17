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

	virtual void Update(double dt);
	void MoveLeft();
	void MoveRight();
	void Boost();

	void Draw() const;

	Utils::CartesianVector GetPosition() const;
	std::string GetName() const;
	bool IsGettingKilled(const Player& killer);
	// Provoque l'explosion en cas de mort

	Player(std::string aName, Utils::CartesianVector initPos,
			Utils::CartesianVector initSpeed, int aNumber);

private:
	static const bool OPTION_WALL_AFTER_DEATH;
	static const float WALL_BASE_HEIGHT;

	std::string name;
	Vehicle myVehicle;
	Wall myWall;
	Utils::CartesianVector initPosition;
	bool isAlive;
	int playerNumber;
};

#endif /* PLAYER_H_ */
