// Menu.h
// Déclaration de la classe Menu

#ifndef __MENU_H__
#define __MENU_H__

#include "Singleton.h"
#include "AbstractCamera.h"

class Menu : public Singleton<Menu>
{
  friend class Singleton<Menu>;

public:	
	static const int BUTTON_COUNT = 3;
	enum ButtonEnum { SOLO, SETTINGS, QUIT };

	static void OnKeyDown( int keyboardContext, int keyCode );
	static void OnKeyUp( int keyboardContext, int keyCode );

	void Init ( );
	void Free ( );
	void Update ( );
	void Draw ( );

	ButtonEnum GetButtonPointer ( );
	void SetButtonPointer ( ButtonEnum aButton );


protected:
	ButtonEnum nButtonPointer;
	AbstractCamera *currentCamera;

private:
	// Constructeur
	Menu ( );

	// Destructeur
	~Menu ( );
};


#endif // __MENU_H__*/