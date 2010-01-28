// Computer.cpp
// Definition de la classe Computer

#include "Computer.h"
#include "Game.h"

const int V_PLAYER = 1;
const int V_WALL = 2;

/******************************************************************************
*                              Mise a jour                                    *
******************************************************************************/
void Computer::Update ( double dt )
{
	artificialIntelligence ( );
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
void Computer::artificialIntelligence ( )
{
	// On remplit la matrice avec les objets connus
	getInformationBySenses ( );

	// On pèse le contre de chaque possibilité 
	int consLeft = getAgainstBySensoryMemory ( -1 );
	int consRight = getAgainstBySensoryMemory ( 1 );
	int consForward = getAgainstBySensoryMemory ( 0 );

	// On effectue le choix en fonction des poids des contre.
	if ( ( consRight < consLeft ) && ( consRight < consForward ) )
	{
		MoveRight ( );
	}
	else if ( consLeft < consForward )
	{
		MoveLeft ( );
	}

	



}

// Initialisation la variable contentPlane
void Computer::getInformationBySenses ( )
{
	Game* aGame = Game::GetInstance ( );
	int xPlane = aGame->GetPlane ( )->GetX ( );
	int zPlane = aGame->GetPlane ( )->GetZ ( );
	int x, z;
	Utils::CartesianVector cPoint, oldPoint;

	// Initialisation de la matrice à 0
	for ( int i = 0; i < SIZE_X; i++ )
	{
		for ( int j = 0; j < SIZE_Z; j++ )
		{
			contentPlane [ i ][ j ] = 0;
		}
	}

	// Ajout des objets/contenus à la matrice
	Player** tabPlayers = aGame->GetPlayers ( );
	for ( int i = 0; i < aGame->GetNbrPlayers ( ); i++ )
	{
		if ( tabPlayers[i]->IsAlive ( ) )
		{
			// Ajout des joueurs à contentPlane
			x = floor( tabPlayers[i]->GetPosition().x * 2 ); // Arrondi inférieur : float -> int
			z = floor( tabPlayers[i]->GetPosition().z * 2 );
			if ( ( x >= 0 ) && ( x < SIZE_X ) && ( z >= 0 ) && ( z <= SIZE_Z ) )
			{
				contentPlane[ x ][ z ] |= V_PLAYER; // On indique qu'il y a un joueur
			}
			
			// Ajout des murs à contentPlane
			if ( tabPlayers[i]->GetWall ( )->GetVertexesCount ( ) >= 1 )
			{
				tabPlayers[i]->GetWall ( )->GetVertexe ( oldPoint, 0 );
			}

			for ( unsigned int j = 1; j < tabPlayers[i]->GetWall ( )->GetVertexesCount ( ); j++ )
			{
				tabPlayers[i]->GetWall ( )->GetVertexe ( cPoint, j );
				// Pour toutes les cases qui contiennent un mur, on l'ajoute.
				if ( abs ( oldPoint.x - cPoint.x ) > abs ( oldPoint.z - cPoint.z ) )
				{
					z = floor ( oldPoint.z + cPoint.z );
					for ( x = min ( floor ( oldPoint.x * 2 ), floor ( cPoint.x * 2 ) );
							x <= max ( floor ( oldPoint.x * 2 ), floor ( cPoint.x * 2 ) ); x++ )
					{
						if ( ( x >= 0 ) && ( x < SIZE_X ) && ( z >= 0 ) && ( z <= SIZE_Z ) )
						{
							contentPlane[ x ][ z ] |= V_WALL;
						}
					}
				}
				else
				{
					x = floor ( oldPoint.x + cPoint.x );
					for ( z = min ( floor ( oldPoint.z * 2 ), floor ( cPoint.z * 2 ) );
							z <= max ( floor ( oldPoint.z * 2 ), floor ( cPoint.z * 2 ) ); z++ )
					{
						if ( ( x >= 0 ) && ( x < SIZE_X ) && ( z >= 0 ) && ( z <= SIZE_Z ) )
						{
							contentPlane[ x ][ z ] |= V_WALL;
						}
					}
				}
			}
		}
	}
}

// Renvoie le poids du contre 
int Computer::getAgainstBySensoryMemory ( int dl )
{
	/*** Initialisation ***/
	int weightOfCons = 0; // Poids du contre
	// Direction
	int dx, dz;           
	if ( abs( myVehicle.GetSpeed ( ).x ) > abs( myVehicle.GetSpeed ( ).z ) )
	{
		 dx = myVehicle.GetSpeed ( ).x / abs ( myVehicle.GetSpeed ( ).x );
		 dz = 0;
	}
	else
	{
		dx = 0;
		dz = myVehicle.GetSpeed ( ).z / abs ( myVehicle.GetSpeed ( ).z );
	}
	// Position actuelle
	int currX = floor ( myVehicle.GetPosition ( ).x * 2 );
	int currZ = floor ( myVehicle.GetPosition ( ).z * 2 );
	// Positions suivantes
	int newX, newZ;
	if ( dl != 0 )
	{
		newX = currX + dl * dz;
		newZ = currZ - dl * dx;
	}
	else
	{
		newX = currX + dx;
		newZ = currZ + dz;
	}
	int forward2X = 2 * newX - currX;
	int forward2Z = 2 * newZ - currZ;
	int forward3X = 3 * newX - 2 * currX;
	int forward3Z = 3 * newZ - 2 * currZ;
	int forward4X = 4 * newX - 3 * currX;
	int forward4Z = 4 * newZ - 3 * currZ;
	int leftX = newX - newZ + currZ;
	int leftZ = newZ + newX - currX;
	int rightX = newX + newZ - currZ;
	int rightZ = newZ - newX + currX;

	/*** Pesée du contre ***/
	// Il y a grand danger si on sort de la carte
	if ( ( newX < 0 ) || ( newX >= SIZE_X ) || ( newZ < 0 ) || ( newZ >= SIZE_Z )
		|| ( forward2X < 0 ) || ( forward2X >= SIZE_X ) || ( forward2Z < 0 ) || ( forward2Z >= SIZE_Z )
		|| ( forward3X < 0 ) || ( forward3X >= SIZE_X ) || ( forward3Z < 0 ) || ( forward3Z >= SIZE_Z )
		|| ( leftX < 0 ) || ( leftX >= SIZE_X ) || ( leftZ < 0 ) || ( leftZ >= SIZE_Z )
		|| ( rightX < 0 ) || ( rightX >= SIZE_X ) || ( rightZ < 0 ) || ( rightZ >= SIZE_Z ) )
	{
		weightOfCons += 8192;
	}
	else if ( ( forward4X < 0 ) || ( forward4X >= SIZE_X ) || ( forward4Z < 0 ) || ( forward4Z >= SIZE_Z ))
	{
		weightOfCons += 4096;
	}
	else
	{
		// Il y a grand danger si on rencontre un joueur.
		if ( ( ( contentPlane [ newX ][ newZ ] & V_PLAYER ) > 0 )
			|| ( ( contentPlane [ forward2X ][ forward2Z ] & V_PLAYER ) > 0 )
			|| ( ( contentPlane [ forward3X ][ forward3Z ] & V_PLAYER ) > 0 )
			|| ( ( contentPlane [ leftX ][ leftZ ] & V_PLAYER ) > 0 )
			|| ( ( contentPlane [ rightX ][ rightZ ] & V_PLAYER ) > 0 ) )
		{
			weightOfCons += 8192;
		}
		else if ( ( contentPlane [ forward4X ][ forward4Z ] & V_PLAYER ) > 0 )
		{
			weightOfCons += 4096;
		}
		// Il y a grand danger si on rencontre un mur.
		if ( ( ( contentPlane [ newX ][ newZ ] & V_WALL ) > 0 )
			|| ( ( contentPlane [ forward2X ][ forward2Z ] & V_WALL ) > 0 )
			|| ( ( contentPlane [ forward3X ][ forward3Z ] & V_WALL ) > 0 )
			|| ( ( contentPlane [ leftX ][ leftZ ] & V_WALL ) > 0 )
			|| ( ( contentPlane [ rightX ][ rightZ ] & V_WALL ) > 0 ) )
		{
			weightOfCons += 8192;
		}
		else if ( ( contentPlane [ forward4X ][ forward4Z ] & V_WALL ) > 0 )
		{
			weightOfCons += 4096;
		}
	}


	return weightOfCons;
}