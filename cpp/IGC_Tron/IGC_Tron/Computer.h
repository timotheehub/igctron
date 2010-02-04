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
	void artificialIntelligence ( );
	void getInformationBySenses ( );
	int getAgainstBySensoryMemory ( int dl );
	void getBoundsOfVehicle ( int & minX, int & maxX, int & minZ, int & maxZ,
								int & dl, Vehicle * vehicle );

	static const int SIZE_X = 40;
	static const int SIZE_Z = 60;
	int contentPlane [ SIZE_X ][ SIZE_Z ]; // Contient les �l�ments du plateau
};

#endif // __COMPUTER_H__


