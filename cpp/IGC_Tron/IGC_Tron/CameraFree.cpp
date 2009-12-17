// CameraFree.h
// Definition de la classe CameraFree

#include "CameraFree.h"
#include "Displayer.h"

const float CameraFree::MOVE_SPEED = 50.0f;

/******************************************************************************
*                             Mise a jour                                     *
******************************************************************************/
void CameraFree::Update ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	float dt = aDisplayer->GetDelta();

	if ( moveForward )
		aCamera->moveForward( MOVE_SPEED * dt );
	if ( moveBackward )
		aCamera->moveBackward( MOVE_SPEED * dt );
	if ( strafeLeft )
		aCamera->moveLeft( MOVE_SPEED * dt );
	if ( strafeRight )
		aCamera->moveRight( MOVE_SPEED * dt );

	AbstractCamera::Update ( );
}

/******************************************************************************
*                    Constructeur et destructeur                              *
******************************************************************************/
CameraFree::CameraFree ( )
: AbstractCamera ( ), moveForward ( false ), moveBackward ( false ),
strafeLeft ( false ), strafeRight ( false )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Window* window = aDisplayer->GetWindow ( );

	aCamera->setRatio( window->getInnerWidth(), window->getInnerHeight() );
	aCamera->setCenter( 20.0f, 20.0f, 0.0f );
	aCamera->lookAt( -0.1f, -1.0f, 0.0f );
	aCamera->update();
}

CameraFree::~CameraFree ( )
{
}
