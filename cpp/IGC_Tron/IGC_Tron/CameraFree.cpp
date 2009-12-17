// CameraFree.h
// Definition de la classe CameraFree

#include "CameraFree.h"
#include "Displayer.h"
#include "Globals.h"

using namespace KeyCodes;

const float CameraFree::MOVE_SPEED = 50.0f;
bool CameraFree::moveForward = false;
bool CameraFree::moveBackward = false;
bool CameraFree::strafeLeft = false;
bool CameraFree::strafeRight = false;

/******************************************************************************
*                    Gestion des evenements                                   *
******************************************************************************/
void CameraFree::OnKeyDown( int keyboardContext, int keyCode )
{
	switch ( keyCode )
	{
		case Z:
			moveForward = true;
			break;
		case S:
			moveBackward = true;
			break;
		case Q:
			strafeLeft = true;
			break;
		case D:
			strafeRight = true;
			break;
	}
}

void CameraFree::OnKeyUp( int keyboardContext, int keyCode )
{
	switch ( keyCode )
	{
		case Z:
			moveForward = false;
			break;
		case S:
			moveBackward = false;
			break;
		case Q:
			strafeLeft = false;
			break;
		case D:
			strafeRight = false;
			break;
	}
}

/******************************************************************************
*                       Initialise et détruit                                 *
******************************************************************************/
void CameraFree::Init ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterKeys ( OnKeyDown, OnKeyUp );
}

void CameraFree::Free ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( OnKeyDown, OnKeyUp );
}

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
: AbstractCamera ( )
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
