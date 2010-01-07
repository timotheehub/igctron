// Settings.h
// Déclaration de la classe Settings

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "Singleton.h"
#include "Game.h"

struct PlayerSettings
{
	int TurnLeft;
	int TurnRight;
};

struct CameraSettings
{
	int NextCamera;
	int PreviousCamera;
};

class Settings : public Singleton<Settings>
{
  friend class Singleton<Settings>;

public:
	inline const PlayerSettings* GetPlayerSettings ( int number );
	inline const CameraSettings* GetCameraSettings ( );
	Settings ( );

protected:
	PlayerSettings tabPlayersSettings [ Game::MAX_PLAYERS ];
	CameraSettings aCameraSettings;

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
inline const CameraSettings* Settings::GetCameraSettings ( )
{
	return &aCameraSettings;
}

#endif // __SETTINGS_H__ */