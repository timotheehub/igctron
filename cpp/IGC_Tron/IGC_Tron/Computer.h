// Computer.h
// Declaration de la classe Computer

#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "Player.h"

class Computer : public Player
{
public:
	void Update ( double dt );

	Computer ( std::string aName, Utils::CartesianVector initPos,
			Utils::CartesianVector initSpeed, int aNumber );
	~Computer ( );

protected:
	void ArtificielIntelligence ( );
};

#endif // __COMPUTER_H__


