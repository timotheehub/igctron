// CameraFree.h
// Definition de la classe CameraFree

#include "CameraFree.h"
#include "Displayer.h"
#include "Globals.h"

using namespace KeyCodes;

const float CameraFree::MOVE_SPEED = 50.0f;
const float CameraFree::MOUSE_SENSITIVITY = 5.0f;
bool CameraFree::moveForward = false;
bool CameraFree::moveBackward = false;
bool CameraFree::strafeLeft = false;
bool CameraFree::strafeRight = false;
int CameraFree::mouseLastX = 0;
int CameraFree::mouseLastY = 0;

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

void CameraFree::OnMouseMove ( int keyboardContext, int mouseContext,
									int mouseX, int mouseY )
{
	if ( mouseContext & IWindow::MC_LEFT )
	{
		float dx = MOUSE_SENSITIVITY * (float)(mouseX - mouseLastX);
		float dy = MOUSE_SENSITIVITY * (float)(mouseY - mouseLastY);

		//aCamera->rotate( dx, dy, 0.0f );
	}

	mouseLastX = mouseX;
	mouseLastY = mouseY;
}

/******************************************************************************
*                       Initialise et detruit                                 *
******************************************************************************/
void CameraFree::Init ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterKeys ( OnKeyDown, OnKeyUp );
	aDisplayer->RegisterMouseMove ( OnMouseMove );
}

void CameraFree::Free ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterKeys ( OnKeyDown, OnKeyUp );
	aDisplayer->UnregisterMouseMove ( OnMouseMove );

	aCamera->setCenter( 20.0f, 20.0f, 0.0f );
	aCamera->lookAt( -0.1f, -1.0f, 0.0f );
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
	Factory* aFactory = aDisplayer->GetFactory();
	aCamera = aFactory->acquire( (IGC::Camera*)NULL, "camera_free" );
	IGC::Window* window = aDisplayer->GetWindow ( );

	aCamera->setRatio( window->getInnerWidth(), window->getInnerHeight() );
	aCamera->setCenter( 30.0f, 20.0f, 15.0f );
	aCamera->lookAt( -10.1f, -1.0f, 15.0f );
	aCamera->update();
}

CameraFree::~CameraFree ( )
{
}
