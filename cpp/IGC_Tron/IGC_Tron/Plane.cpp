// Menu.cpp
// D�finition de la classe Plane

#include "Plane.h"
#include "Displayer.h"

/******************************************************************************
*                                Affichage                                    *
******************************************************************************/
void Plane::Draw ( )
{
	Displayer *aDisplayer = Displayer::GetInstance ();
	IGC::Factory *factory = aDisplayer->GetFactory ( );
			
	Model* model = factory->acquire( (IGC::Model*)NULL, "model_plane" );
	model->render();
}

/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************/
Plane::Plane ( int aWidth, int aHeight )
: width ( aWidth ), height ( aHeight )
{
}

Plane::~Plane ()
{
}