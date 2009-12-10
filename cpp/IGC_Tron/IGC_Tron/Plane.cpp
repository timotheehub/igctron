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
	IGC::Texture* texture = factory->acquire( (IGC::Texture*)NULL, "plane_tile" );
			
	Model* model = factory->acquire( (IGC::Model*)NULL, "model_plane" );
	texture->bind();
	model->render();
}

/******************************************************************************
*                 Constructeurs et destructeurs                               *
******************************************************************************/
Plane::Plane ( int zValue, int xValue )
: z ( zValue ), x ( xValue )
{
}

Plane::~Plane ()
{
}
