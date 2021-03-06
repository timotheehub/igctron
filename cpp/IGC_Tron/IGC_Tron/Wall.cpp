/*
 * Wall.cpp
 *
 *  Created on: 3 déc. 2009
 *      Author: fenrhil
 */

#include <vector>
#include "Wall.h"
#include "Globals.h"
#include "Displayer.h"
using namespace std;
using namespace Utils;

const float Wall::COLLAPSE_RELATIVE_STEP = 1;

void Wall::Init (const CartesianVector& origin,
		const CartesianVector& direction, float4 color)
{
	xDirection = fabs(direction.x) > fabs(direction.z);

	clear();
	vertexes.assign(1, origin);
	AddVertex();

	height = baseHeight;

	material->setEmissiveColor( color );
}

void Wall::clear()
{
	IGC::Factory *factory = Displayer::GetInstance()->GetFactory();
	vector<IGC::Model*>::const_iterator itm;
	for (itm = models.begin(); itm != models.end(); ++itm)
	{
		factory->release(*itm);
	}
	models.clear();
	vertexes.clear();
}

void Wall::SetLastVertex(const CartesianVector& value)
{
	*vertexes.rbegin() = value;
}

void Wall::AddVertex()
{
	vertexes.push_back(*vertexes.rbegin());

	addModel();
}

void Wall::addModel()
{
	IGC::Factory *factory = Displayer::GetInstance()->GetFactory();
	models.push_back(factory->acquire((IGC::Model*) NULL));
	if (xDirection)
	{
		Model * modelWall = factory->acquire((IGC::Model*) NULL, "model_wallX");
		models.back()->Clone(modelWall);
		factory->release(modelWall);
	}
	else
	{
		Model * modelWall = factory->acquire((IGC::Model*) NULL, "model_wallZ");
		models.back()->Clone(modelWall);
		factory->release(modelWall);
	}
	xDirection = !xDirection;
}

void Wall::Collapse(double dt)
{
	if (height > 0)
	{
		height -= dt * COLLAPSE_RELATIVE_STEP * baseHeight;
	}
	else
	{
		if (!models.empty())
		// On considère que si 'models' est vide, le mur est déjà "vidé"
		{
			clear();
		}
	}
}

void Wall::Draw() const
{
	if (height > 0)
	{
		Displayer *aDisplayer = Displayer::GetInstance();
		IGC::Renderer *renderer = aDisplayer->GetRenderer();
		IGC::Factory *factory = aDisplayer->GetFactory();

		IGC::Texture* texture = factory->acquire((IGC::Texture*) NULL, "plane_tile" ); 
		texture->unbind();
		factory->release ( texture );

		renderer->setTransparency(false);

		material->bind(); // NB : comme pour les textures on bind avant de faire le rendu

		// Mise à jour du dernier IGC::Model
		vector<CartesianVector>::const_reverse_iterator
				it1 = vertexes.rbegin(), it2 = it1++;
		vector<IGC::Model*>::const_reverse_iterator itm = models.rbegin();

		double sizeX = fabs(it1->x - it2->x);
		double sizeZ = fabs(it1->z - it2->z);
		if (sizeX > sizeZ)
		{
			(*itm)->setSize(sizeX, 1.0f, height);
		}
		else
		{
			(*itm)->setSize(sizeZ, 1.0f, height);
		}
		(*itm)->setCenter((it1->x + it2->x) / 2, height/2, (it1->z + it2->z) / 2);

		// Affichage des IGC::Model
		if (height < baseHeight)
		{
			for (itm = models.rbegin(); itm != models.rend(); itm++)
			{
				float3 size = (*itm)->getSize();
				(*itm)->setSize(size.x, size.y, height);
				(*itm)->render();
			}
		}
		else
		{
			for (itm = models.rbegin(); itm != models.rend(); itm++)
			{
				(*itm)->render();
			}
		}

		material->unbind(); // NB : et comme pour les textures on unbind après
	}
}

bool Wall::IsInCollision(const Utils::Rectangle& object) const
{
	vector<CartesianVector>::const_iterator it1 = vertexes.begin();
	if (it1 == vertexes.end())
	{
		return false;
	}
	else
	{
		vector<CartesianVector>::const_iterator it2 = it1++;
		for ( ; it1 != vertexes.end() && !object.IsInCollision(*it1, *it2) ;
				it2 = it1++ )
		{
			 // Bloc vide
		}
		return it1 != vertexes.end();
	}
}

Wall::Wall (float userBaseHeight) :
	vertexes(1), models(), xDirection(true), baseHeight(userBaseHeight),
	height(userBaseHeight)
{
	Factory* factory = Displayer::GetInstance()->GetFactory();

	material = factory->acquire( (IGC::Material*)NULL );
	IGC::Material * wallMaterial = factory->acquire((IGC::Material*)NULL,
			"wall_material");
	material->Clone(wallMaterial);
	factory->release(wallMaterial);

	AddVertex();
}


Wall::~Wall ( )
{
	clear ( );
	
	IGC::Factory *factory = Displayer::GetInstance()->GetFactory();
	factory->release ( material );
}

