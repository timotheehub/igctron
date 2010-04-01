// Settings.h
// Déclaration de la classe Settings

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <string>

#include "Singleton.h"
#include "Game.h"

struct PlayerSettings
{
	int TurnLeft;
	int TurnRight;
	int Boost;
	float4 vehicleColor;
	float4 wallColor;
	std::string modelName;
	std::string playerName;
};

struct GlobalSettings
{
	int NextCameraKeyCode;
	int PreviousCameraKeyCode;
	double BoostCoef;
	double BoostLength;
};

class Settings : public Singleton<Settings>
{
  friend class Singleton<Settings>;

public:
	inline const PlayerSettings* GetPlayerSettings ( int number );
	inline const GlobalSettings* GetGlobalSettings ( );
	Settings ( );

protected:
	PlayerSettings tabPlayersSettings [ Game::MAX_PLAYERS ];
	GlobalSettings aGlobalSettings;

private:
};

// Renvoie les touches d'un joueur
inline const PlayerSettings* Settings::GetPlayerSettings ( int number )
{
	if ( ( number >= 0 ) && ( number < Game::MAX_PLAYERS ) )
	{
		return &tabPlayersSettings[number];
	}
	else 
	{	
		return 0;
	}
}

// Renvoie les touches d'un joueur
inline const GlobalSettings* Settings::GetGlobalSettings ( )
{
	return &aGlobalSettings;
}

#endif // __SETTINGS_H__ */
