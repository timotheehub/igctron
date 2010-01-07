// CameraFree.h
// Declaration de la classe CameraFree

#ifndef __CAMERA_FREE_H__
#define __CAMERA_FREE_H__

#include "AbstractCamera.h"

class CameraFree : public AbstractCamera 
{
public:
	// Gestion des touches
	static void OnKeyDown( int keyboardContext, int keyCode );
	static void OnKeyUp( int keyboardContext, int keyCode );
	static void OnMouseMove ( int keyboardContext, int mouseContext,
									int mouseX, int mouseY );

	// Met à jour
	void Update ( );

	// Pour pouvoir réutiliser la caméra sans la détruire
	void Init ( );
	void Free ( );

	// Constructeur et destructeur
	CameraFree ( );
	~CameraFree ( );

protected:
	// Constantes statiques
	static const float MOVE_SPEED;
	static const float MOUSE_SENSITIVITY;

	// Variables statiques de translation
	static bool moveForward;
	static bool moveBackward;
	static bool strafeLeft;
	static bool strafeRight;

	// Variables statiques de position de souris
	static int mouseLastX;
	static int mouseLastY;
};

#endif // __CAMERA_FREE_H__