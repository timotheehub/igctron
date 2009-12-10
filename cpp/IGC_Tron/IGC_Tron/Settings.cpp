// Settings.cpp
// Definition de la classe Settings
#include "Settings.h"
#include "Globals.h"

/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************/
// Constructeur
Settings::Settings ( )
{
	tabPlayersSettings [ 0 ].TurnLeft = KeyCodes::LEFT;
	tabPlayersSettings [ 0 ].TurnRight = KeyCodes::RIGHT;
}
