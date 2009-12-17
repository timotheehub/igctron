// Computer.cpp
// Definition de la classe Computer

#include "Computer.h"

/******************************************************************************
*                              Mise a jour                                    *
******************************************************************************/
void Computer::Update ( double dt )
{
	ArtificielIntelligence ( );
	Player::Update ( dt );
}

/******************************************************************************
*                      Constructeur et destructeur                            *
******************************************************************************/
Computer::Computer ( std::string aName, Utils::CartesianVector initPos,
			Utils::CartesianVector initSpeed, int aNumber )
: Player ( aName, initPos, initSpeed, aNumber )
{
}

Computer::~Computer ( )
{
}

/******************************************************************************
*                      Intelligence artificielle                              *
******************************************************************************/
void Computer::ArtificielIntelligence ( )
{

}