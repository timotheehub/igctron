// CameraFree.h
// Declaration de la classe CameraFree

#ifndef __CAMERA_FREE_H__
#define __CAMERA_FREE_H__

#include "AbstractCamera.h"

class CameraFree : public AbstractCamera 
{
public:
	void Update ( );

	CameraFree ( );
	~CameraFree ( );

protected:
	static const float MOVE_SPEED;

	bool moveForward;
	bool moveBackward;
	bool strafeLeft;
	bool strafeRight;
};

#endif // __CAMERA_FREE_H__