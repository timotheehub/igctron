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

	// Met à jour
	void Update ( );

	// Pour pouvoir réutiliser la caméra sans la détruire
	void Init ( );
	void Free ( );

	// Constructeur et destructeur
	CameraFree ( );
	~CameraFree ( );

protected:
	// Variables static
	static const float MOVE_SPEED;

	static bool moveForward;
	static bool moveBackward;
	static bool strafeLeft;
	static bool strafeRight;
};

#endif // __CAMERA_FREE_H__