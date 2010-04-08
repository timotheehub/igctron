// Game.h
// Declaration de la classe Game

#ifndef __GAME_H__
#define __GAME_H__

#include "Player.h"
#include "Singleton.h"
#include "Plane.h"
#include "SimpleMutex.h"
#include "AbstractCamera.h"
#include "CameraFree.h"
#include "CameraOverall.h"
#include "CameraPlayer.h"

#include <string>


struct PlayerInfos
{
	enum TypePlayer { NO, KEYBOARD, COMPUTER };
	TypePlayer ATypePlayer;
	std::string Name; 
};

class Game : public Singleton<Game>
{
  friend class Singleton<Game>;

public:
	static const int MAX_PLAYERS = 4;
	static const int MAX_CAMERAS = 3;
	static void OnKeyDown( int keyboardContext, int keyCode );
	static void OnKeyUp( int keyboardContext, int keyCode );

	void Init ( );
	void Free ( );

	void Update ( );

	void Draw ( );

	inline Player ** GetPlayers ( );
	inline int GetNbrPlayers ( );

	inline void MutexAcquireLock ( );
	inline void MutexReleaseLock ( );
	inline const Plane* GetPlane ( ) const;
	inline void SetPreviousCamera ( );
	inline void SetNextCamera ( );

protected:
	// Joueurs et plateau
	Player** tabPlayersIndex;
	Player* tabPlayers [ MAX_PLAYERS ];
	bool * tabPlayersAlive;
	int nbPlayers;
	Plane *aPlane;

	// Cameras
	AbstractCamera *tabCameras [ MAX_CAMERAS ];
	int nCurrentCamera;
	CameraOverall cameraOverall;
	CameraFree cameraFree;
	CameraPlayer cameraPlayer;

	// Mutex
	SimpleMutex aMutex;

private:
	// Constructeur
	Game ( );

	// Destructeur
	~Game ( );
};

inline Player** Game::GetPlayers ( )
{
	return tabPlayersIndex;
}

inline int Game::GetNbrPlayers ( )
{
	return nbPlayers;
}


inline void Game::MutexAcquireLock ( )
{
	aMutex.AcquireLock ( );
}

inline void Game::MutexReleaseLock ( )
{
	aMutex.ReleaseLock ( );
}

inline const Plane* Game::GetPlane ( ) const
{
	return aPlane;
}

inline void Game::SetNextCamera ( )
{
	tabCameras[nCurrentCamera]->Free();
	nCurrentCamera = (nCurrentCamera + 1) % MAX_CAMERAS;
	tabCameras[nCurrentCamera]->Init();
}

inline void Game::SetPreviousCamera ( )
{
	tabCameras[nCurrentCamera]->Free();
	nCurrentCamera = (nCurrentCamera - 1 + MAX_CAMERAS) % MAX_CAMERAS;
	tabCameras[nCurrentCamera]->Init();
}
	
#endif // __MENU_H__*/
