// CameraPlayer.h
// Declaration de la classe CameraPlayer

#ifndef __CAMERA_PLAYER_H__
#define __CAMERA_PLAYER_H__

#include "AbstractCamera.h"
#include "Vehicle.h"

class CameraPlayer : public AbstractCamera 
{
public:
	// Gestion de la souris
	static void OnMouseMove ( int keyboardContext, int mouseContext,
									int mouseX, int mouseY );

	// Met à jour
	void Update ( double dt );

	// Pour pouvoir réutiliser la caméra sans la détruire
	void Init ( );
	void Free ( );

	// Constructeur et destructeur
	CameraPlayer ( int i );
	~CameraPlayer ( );

protected:
	Vehicle * monVehicle;
	int nVehicle;

	// Constantes statiques
	static const float MOVE_SPEED;
	static const float MOUSE_SENSITIVITY;

	// Variables statiques de position de souris
	static int mouseLastX;
	static int mouseLastY;
};

#endif // __CAMERA_PLAYER_H__
