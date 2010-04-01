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
	aGlobalSettings.PreviousCameraKeyCode = KeyCodes::F1;
	aGlobalSettings.NextCameraKeyCode = KeyCodes::F2;
	aGlobalSettings.BoostCoef = 3.0;
	aGlobalSettings.BoostLength = 3.0;

	tabPlayersSettings [ 0 ].vehicleColor = make_float4(1.0f, 0.0f, 0.0f, 1.0f);
	tabPlayersSettings [ 1 ].vehicleColor = make_float4(1.0f, 1.0f, 0.0f, 1.0f);
	tabPlayersSettings [ 2 ].vehicleColor = make_float4(1.0f, 0.0f, 1.0f, 1.0f);
	tabPlayersSettings [ 3 ].vehicleColor = make_float4(0.0f, 0.0f, 1.0f, 1.0f);

	for ( int i = 0 ; i < Game::MAX_PLAYERS ; ++i )
	{
		tabPlayersSettings [ i ].wallColor =
			0.7f * tabPlayersSettings [ i ].vehicleColor ;
		tabPlayersSettings [ i ].wallColor.w = 1.0f;

		tabPlayersSettings [ i ].TurnLeft = KeyCodes::LEFT;
		tabPlayersSettings [ i ].TurnRight = KeyCodes::RIGHT;
		tabPlayersSettings [ i ].Boost = KeyCodes::ENTER;
		tabPlayersSettings [ i ].modelName = "model_motorbike";
	}

	tabPlayersSettings [ 0 ].playerName = "Bozo"; 
	tabPlayersSettings [ 1 ].playerName = "Computer 1"; 
	tabPlayersSettings [ 2 ].playerName = "Computer 2"; 
	tabPlayersSettings [ 3 ].playerName = "Computer 3"; 
}
