// AbstractCamera.h
// Definition de la classe AbstractCamera

#include "AbstractCamera.h"
#include "Displayer.h"

/******************************************************************************
*                                Mise à jour                                  *
******************************************************************************/
void AbstractCamera::Update ( )
{
	aCamera->bind();
}

/******************************************************************************
*                      Initialisation et destruction                          *
******************************************************************************/
void AbstractCamera::Init ( )
{
}

void AbstractCamera::Free ( )
{
}

/******************************************************************************
*                     Constructeur et destructeur                             *
******************************************************************************/
AbstractCamera::AbstractCamera ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Factory *factory = aDisplayer->GetFactory ( );
	aCamera = factory->acquire( (IGC::Camera*)NULL );
}

AbstractCamera::~AbstractCamera ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Factory *factory = aDisplayer->GetFactory ( );
	factory->release ( aCamera );
}