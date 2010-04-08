// CameraPlayer.h
// Definition de la classe CameraPlayer

#include "CameraPlayer.h"
#include "Displayer.h"
#include "Game.h"
#include "Globals.h"
#include "CartesianVector.h"

using namespace KeyCodes;

const float CameraPlayer::MOVE_SPEED = 50.0f;
const float CameraPlayer::MOUSE_SENSITIVITY = 5.0f;
int CameraPlayer::mouseLastX = 0;
int CameraPlayer::mouseLastY = 0;
const float D_ANGLE_MIN = 0.01f;

/******************************************************************************
*                    Gestion des evenements                                   *
******************************************************************************/
void CameraPlayer::OnMouseMove ( int keyboardContext, int mouseContext,
									int mouseX, int mouseY )
{
	if ( mouseContext & IWindow::MC_LEFT )
	{
		//float dx = MOUSE_SENSITIVITY * (float)(mouseX - mouseLastX);
		//float dy = MOUSE_SENSITIVITY * (float)(mouseY - mouseLastY);

		//aCamera->rotate( dx, dy, 0.0f );
	}

	mouseLastX = mouseX;
	mouseLastY = mouseY;
}

/******************************************************************************
*                       Initialise et detruit                                 *
******************************************************************************/
void CameraPlayer::Init ( )
{
	// Initialise monVehicle
	Game *aGame = Game::GetInstance ( );
	if ( ( nVehicle >= 0 ) && ( nVehicle < aGame->GetNbrPlayers( ) ) )
	{
		monVehicle = aGame->GetPlayers()[nVehicle]->GetVehicle();
	}

	// Initialisation de la camera
	aCamera->lookAt ( monVehicle->GetPosition().x,
				 monVehicle->GetPosition().y, monVehicle->GetPosition().z );
	Utils::CartesianVector cVector = monVehicle->GetSpeed ( );
	if ( abs ( cVector.x ) > abs ( cVector.z ) )
	{
		aCamera->setCenter ( monVehicle->GetPosition().x - cVector.x,
			monVehicle->GetPosition().y + 5, monVehicle->GetPosition().z );
	}
	else
	{
		aCamera->setCenter ( monVehicle->GetPosition().x,
			monVehicle->GetPosition().y + 5, monVehicle->GetPosition().z - cVector.z );
	}

	// Souris
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->RegisterMouseMove ( OnMouseMove );
}

void CameraPlayer::Free ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ( );
	aDisplayer->UnregisterMouseMove ( OnMouseMove );

	aCamera->setCenter( 20.0f, 20.0f, 0.0f );
	aCamera->lookAt( -0.1f, -1.0f, 0.0f );
}

/******************************************************************************
*                             Mise a jour                                     *
******************************************************************************/
void CameraPlayer::Update ( double dt )
{
	static const double COEF = 0.04;
	if ( monVehicle != 0 )
	{
		float3 oldCenter = aCamera->getCenter ( );
		float3 vehiclePos = monVehicle->GetPosition();
		float3 goalCenter;

		aCamera->lookAt ( vehiclePos );

		// TODO : pourquoi ça marche pas ???
		//goalCenter = vehiclePos - dt * monVehicle->GetSpeed ( );
		goalCenter = vehiclePos - monVehicle->GetSpeed ( );
		goalCenter.y += 5;

		// TODO : use dt
		//aCamera->setCenter ( NEW_COEF*goalCenter + OLD_COEF*oldCenter );
		double coef = std::pow(COEF,dt);
		aCamera->setCenter ( coef*oldCenter + (1-coef)*goalCenter );
	}
}

/******************************************************************************
*                    Constructeur et destructeur                              *
******************************************************************************/
CameraPlayer::CameraPlayer ( int i )
: AbstractCamera ( ), monVehicle ( 0 ), nVehicle ( i )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	Factory* aFactory = aDisplayer->GetFactory();
	aCamera = aFactory->acquire( (IGC::Camera*)NULL );
	IGC::Window* window = aDisplayer->GetWindow ( );

	aCamera->setRatio( window->getInnerWidth(), window->getInnerHeight() );
	aCamera->setCenter( 30.0f, 20.0f, 15.0f );
	aCamera->lookAt( -10.1f, -1.0f, 15.0f );
	aCamera->update();
}

CameraPlayer::~CameraPlayer ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	Factory* aFactory = aDisplayer->GetFactory();
	aFactory->release ( aCamera );
}
