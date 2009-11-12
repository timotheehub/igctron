// Menu.h
// Déclaration de la classe Menu

#ifndef __MENU_H__
#define __MENU_H__

#include "Singleton.h"

class Menu : public Singleton<Menu>
{
  friend class Singleton<Menu>;

public:
	static void OnKeyDown( int keyboardContext, int keyCode );
	static void OnKeyUp( int keyboardContext, int keyCode );

	void Init ( );
	void Free ( );

	void Update ( );

	enum ButtonEnum { SOLO, SETTINGS, QUIT };

protected:
	ButtonEnum nButtonPointer;

private:
	// Constructeur
	Menu ( );

	// Destructeur
	~Menu ( );
};


#endif // __MENU_H__*/