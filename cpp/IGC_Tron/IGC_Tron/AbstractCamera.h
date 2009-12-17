// AbstractCamera.h
// Declaration de la classe AbstractCamera

#ifndef __ABSTRACT_CAMERA_H__
#define __ABSTRACT_CAMERA_H__

#include "D3DCamera.h"
#include "OGLCamera.h"

class AbstractCamera 
{
public:
	virtual void Update ( );

	AbstractCamera ( );
	~AbstractCamera ( );

protected :
	IGC::Camera* aCamera;
};

#endif // __ABSTRACT_CAMERA_H__