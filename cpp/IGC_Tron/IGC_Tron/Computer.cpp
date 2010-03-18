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
//artificialIntelligence ( );
	Player::Update ( dt );
}

/******************************************************************************
*                      Constructeur et destructeur                            *
******************************************************************************/
Computer::Computer ( Utils::CartesianVector initPos,
			Utils::CartesianVector initSpeed, int aNumber )
: Player ( initPos, initSpeed, aNumber )
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
	int consLeft = getAgainstBySensoryMemory ( -1 ) + 512;
	int consRight = getAgainstBySensoryMemory ( 1 ) + 512;
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
		if ( ( tabPlayers[i]->IsAlive ( ) ) )
		{
			// Ajout des joueurs à contentPlane
			x = floor( tabPlayers[i]->GetPosition().x * 2 ); // Arrondi inférieur : float -> int
			z = floor( tabPlayers[i]->GetPosition().z * 2 );
				
			if ( tabPlayers[i] != this ) {
				int minX, maxX, minZ, maxZ;
				x = 0;
				getBoundsOfVehicle ( minX, maxX, minZ, maxZ, x, tabPlayers[i]->GetVehicle() );
				for ( x = minX; x <= maxX; x++ )
				{
					for ( z = minZ; z <= maxZ; z++ )
					{
						contentPlane[ x ][ z ] |= V_PLAYER; // On indique qu'il y a un joueur
					}
				}
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
				// Mur selon x
				if ( abs ( oldPoint.x - cPoint.x ) > abs ( oldPoint.z - cPoint.z ) )
				{
					z = floor ( oldPoint.z + cPoint.z );
					for ( x = min ( floor ( oldPoint.x * 2 ), floor ( cPoint.x * 2 ) );
							x <= max ( floor ( oldPoint.x * 2 ), floor ( cPoint.x * 2 ) ); x++ )
					{
						if ( ( ( x >= 0 ) && ( x < SIZE_X ) && ( z >= 0 ) && ( z <= SIZE_Z ) )
						&& ( ( tabPlayers[i] != this ) || ( j < ( tabPlayers[i]->GetWall ( )->GetVertexesCount ( ) - 1 ) ) ) )
						{
							contentPlane[ x ][ z ] |= V_WALL;
						}
					}
				}
				// Mur selon z
				else
				{
					x = floor ( oldPoint.x + cPoint.x );
					for ( z = min ( floor ( oldPoint.z * 2 ), floor ( cPoint.z * 2 ) );
							z <= max ( floor ( oldPoint.z * 2 ), floor ( cPoint.z * 2 ) ); z++ )
					{
						if ( ( ( x >= 0 ) && ( x < SIZE_X ) && ( z >= 0 ) && ( z <= SIZE_Z ) )
						&& ( ( tabPlayers[i] != this ) || ( j < ( tabPlayers[i]->GetWall ( )->GetVertexesCount ( ) - 1 ) ) ) )
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
	// Bornes suivantes
	int minX, maxX, minZ, maxZ;
	getBoundsOfVehicle ( minX, maxX, minZ, maxZ, dl, &myVehicle );
	
	/*** Pesée du contre ***/
	// Il y a grand danger si on sort de la carte
	if ( ( minX < 0 ) || ( maxX >= SIZE_X ) || ( minZ < 0 ) || ( maxZ >= SIZE_Z ) )
	{
		weightOfCons += 8192;
	}
	else
	{
		// Il y a grand danger si on rencontre un joueur.
		bool isFound = false;
		for ( int i = minX; i <= maxX; i++ )
		{
			for ( int j = minZ; j <= maxZ; j++ )
			{
				if ( ( contentPlane [ i ][ j ] & V_PLAYER ) > 0 )
				{
					isFound = true;
				}
			}
		}
		if ( isFound )
		{
			weightOfCons += 8192;
		}

		// Il y a grand danger si on rencontre un mur.
		isFound = false;
		for ( int i = minX; i <= maxX; i++ )
		{
			for ( int j = minZ; j <= maxZ; j++ )
			{
				if ( ( contentPlane [ i ][ j ] & V_WALL ) > 0 )
				{
					isFound = true;
				}
			}
		}
		if ( isFound )
		{
			weightOfCons += 8192;
		}

		bool isOnObstacle = false;
		// Influence des objets
		for ( int i = 0; i < SIZE_X; i++ )
		{
			for ( int j = 0; j < SIZE_Z; j++ )
			{
				// Même case
				if ( ( i >= minX ) && ( i <= maxX ) && ( j >= minZ ) && ( j <= maxZ ) )
				{
					if ( ( ( contentPlane [ i ][ j ] & V_PLAYER ) > 0 ) 
					|| ( ( contentPlane [ i ][ j ] & V_WALL ) > 0 ) )
					{
						isOnObstacle = true;
					}
				}

				// Même ligne
				if ( ( ( contentPlane [ i ][ j ] & V_PLAYER ) > 0 ) 
				|| ( ( contentPlane [ i ][ j ] & V_WALL ) > 0 ) )
				{
					switch ( dl )
					{
						case 10:
							if ( ( j >= minZ ) && ( j <= maxZ ) && ( i > maxX ) )
							{
								weightOfCons += 2048 / ( i - maxX );
							}
							break;
						case 11:
							if ( ( i >= minX ) && ( i <= maxX ) && ( j > maxZ ) )
							{
								weightOfCons += 2048 / ( j - maxZ );
							}
							break;
						case 12:
							if ( ( j >= minZ ) && ( j <= maxZ ) && ( i < maxX ) )
							{
								weightOfCons += 2048 / ( maxX - i );
							}
							break;
						case 13:
							if ( ( i >= minX ) && ( i <= maxX ) && ( j < maxZ ) )
							{
								weightOfCons += 2048 / ( maxZ - j );
							}
							break;
					}
				}
			}
		}

		if ( isOnObstacle )
		{
			weightOfCons = 8192;
		}
	}


	return weightOfCons;
}


// Calcule les bornes du vehicule
// dl renvoie la direction
// TODO : Définir des constantes à la place de 10,11,12 et 13.
// TODO : Bug au niveau de GetLength.
void Computer::getBoundsOfVehicle ( int & minX, int & maxX, int & minZ, int & maxZ, int & dl, Vehicle * vehicle )
{
	// Calcul de la direction actuelle
	int dx, dz;  
	if ( abs( vehicle->GetSpeed ( ).x ) > abs( vehicle->GetSpeed ( ).z ) )
	{
		 if ( vehicle->GetSpeed ( ).x > 0 )
		 {
			 dx = 1;
		 }
		 else
		 {
			 dx = -1;
		 }
		 dz = 0;
	}
	else
	{
		 dx = 0;
		 if ( vehicle->GetSpeed ( ).z > 0 )
		 {
			 dz = 1;
		 }
		 else
		 {
			 dz = -1;
		 }
	}

	// Position actuelle
	int currX = floor ( vehicle->GetPosition ( ).x * 2 );
	int currZ = floor ( vehicle->GetPosition ( ).z * 2 );

	// Calcul des bornes
	// S'il y a virage
	if ( dl != 0 )
	{
		// Si deplacement actuel sur dz
		if ( dz != 0 )
		{
			if ( dl * dz > 0 ) // Si virage.dx > 0
			{
				minX = currX;
				maxX = currX + ceil ( vehicle->GetLength() * 2 + 2 ) * dl * dz;
				dl = 10;
			}
			else
			{
				minX = currX + ceil ( vehicle->GetLength() * 2 + 2 ) * dl * dz;
				maxX = currX;
				dl = 12;
			}
			minZ = floor ( vehicle->GetPosition ( ).z * 2.f - 0.5f );
			maxZ = floor ( vehicle->GetPosition ( ).z * 2.f + 0.5f );
		}
		// Si deplacement actuel sur dx
		else
		{
			if ( dl * dx < 0 )
			{
				minZ = currZ;
				maxZ = currZ - ceil ( vehicle->GetLength() * 2 + 2 ) * dl * dx;
				dl = 13;
			}
			else
			{
				minZ = currZ - ceil ( vehicle->GetLength() * 2 + 2 ) * dl * dx;
				maxZ = currZ;
				dl = 11;
			}
			minX = floor ( vehicle->GetPosition ( ).x * 2 - 0.5 );
			maxX = floor ( vehicle->GetPosition ( ).x * 2 + 0.5 );
		}
	}
	// S'il n'y a pas de virage
	else
	{
		if ( dx != 0 )
		{
			if ( dx < 0 )
			{
				minX = currX + ceil ( vehicle->GetLength() * 2 + 2 ) * dx;
				maxX = currX;
				dl = 12;
			}
			else
			{
				minX = currX;
				maxX = currX + ceil ( vehicle->GetLength() * 2 + 2 ) * dx;
				dl = 10;
			}
			minZ = floor ( vehicle->GetPosition ( ).z * 2 - 0.5 );
			maxZ = floor ( vehicle->GetPosition ( ).z * 2 + 0.5 );
		}
		else
		{ 
			if ( dz < 0 )
			{
				minZ = currZ + ceil ( vehicle->GetLength() * 2 + 2 ) * dz;
				maxZ = currZ;
				dl = 13;
			}
			else
			{
				minZ = currZ;
				maxZ = currZ + ceil ( vehicle->GetLength() * 2 + 2 ) * dz;
				dl = 11;
			}
			minX = floor ( vehicle->GetPosition ( ).x * 2 - 0.5 );
			maxX = floor ( vehicle->GetPosition ( ).x * 2 + 0.5 );
		}
	}
}
