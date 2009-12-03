// Game.h
// D�claration de la classe Game

#ifndef __GAME_H__
#define __GAME_H__

#include "Player.h"
#include "Singleton.h"
#include "Plane.h"
#include "SimpleMutex.h"
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
	static void OnKeyDown( int keyboardContext, int keyCode );
	static void OnKeyUp( int keyboardContext, int keyCode );

	void Init ( );
	void Free ( );

	void Update ( );

	void Draw ( );

	inline void MutexAcquireLock ( );
	inline void MutexReleaseLock ( );

protected:
	Player** tabPlayersIndex;
	Player* tabPlayers [ MAX_PLAYERS ];
	int nbPlayers;
	Plane *aPlane;
	SimpleMutex aMutex;

private:
	// Constructeur
	Game ( );

	// Destructeur
	~Game ( );
};

inline void Game::MutexAcquireLock ( )
{
	aMutex.AcquireLock ( );
}

inline void Game::MutexReleaseLock ( )
{
	aMutex.ReleaseLock ( );
}

#endif // __MENU_H__*/
