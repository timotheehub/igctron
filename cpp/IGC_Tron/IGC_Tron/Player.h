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

	inline bool IsAlive ( ) const;
	inline Wall * GetWall ( );
	inline Vehicle * GetVehicle ( );

	Utils::CartesianVector GetPosition() const;
	std::string GetName() const;
	bool IsGettingKilled(const Player& killer);
	// Provoque l'explosion en cas de mort

	Player (std::string aName, Utils::CartesianVector initPos,
			Utils::CartesianVector initSpeed, int aNumber);

	virtual ~Player ( );

protected:
	static const bool OPTION_WALL_AFTER_DEATH;
	static const float WALL_BASE_HEIGHT;

	std::string name;
	Vehicle myVehicle;
	Wall myWall;
	Utils::CartesianVector initPosition;
	int playerNumber;

	enum PlayerStatus
	{
		LIVING,
		DYING,
		DEAD
	};
	PlayerStatus status;
};

inline bool Player::IsAlive ( ) const
{
	return status == LIVING;
}

inline Wall * Player::GetWall ( )
{
	return &myWall;
}

inline Vehicle * Player::GetVehicle ( )
{
	return &myVehicle;
}


#endif /* PLAYER_H_ */
