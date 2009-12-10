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

class Settings : public Singleton<Settings>
{
  friend class Singleton<Settings>;

public:
	inline const PlayerSettings* GetPlayerSettings ( int number );
	Settings ( );

protected:
	PlayerSettings tabPlayersSettings [ Game::MAX_PLAYERS ];

private:
};

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

#endif // __SETTINGS_H__ */