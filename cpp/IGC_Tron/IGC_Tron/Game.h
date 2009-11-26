// Game.h
// Déclaration de la classe Game

#ifndef __GAME_H__
#define __GAME_H__

#include "Singleton.h"

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

protected:
	//Player* tabPlayers [ NB_PLAYERS ];
	//Player** tabPlayersIndex;
	int nbPlayers;

private:
	// Constructeur
	Game ( );

	// Destructeur
	~Game ( );
};


#endif // __MENU_H__*/