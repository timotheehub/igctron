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

void Wall::Init(const CartesianVector& origin)
{
	clear();
	vertexes.assign(1, origin);
	AddVertex();
	height = baseHeight;
}

void Wall::clear()
{
	/*IGC::Factory *factory = Displayer::GetInstance()->GetFactory();
	 vector<IGC::Model*>::const_iterator itm;
	 for (itm = models.begin(); itm != models.end(); ++itm)
	 {
	 factory->release(*itm);
	 }*/
	// TODO : faire fonctionner les release... Actuellement, problèmes d'accès mémoire... ?
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
		models.back()->Clone(
				factory->acquire((IGC::Model*) NULL, "model_wallX"));
	}
	else
	{
		models.back()->Clone(
				factory->acquire((IGC::Model*) NULL, "model_wallZ"));
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

		IGC::Texture* texture = factory->acquire((IGC::Texture*) NULL,
				"logo_orange"); // TODO : release ?
		texture->bind();
		renderer->setTransparency(false);

		// Mise à jour du dernier IGC::Model
		vector<CartesianVector>::const_reverse_iterator
				it1 = vertexes.rbegin(), it2 = it1++;
		vector<IGC::Model*>::const_reverse_iterator itm = models.rbegin();

		if (fabs(it1->x - it2->x) > fabs(it1->z - it2->z))
		{
			(*itm)->setSize(fabs(it1->x - it2->x), height, 1.0f);
		}
		else
		{
			(*itm)->setSize(1.0f, height, fabs(it1->z - it2->z));
		}
		(*itm)->setCenter(fabs(it1->x + it2->x) / 2 - 10, 0.5f, fabs(it1->z
				+ it2->z) / 2 - 15);

		// Affichage des IGC::Model
		if (height < baseHeight)
		{
			for (itm = models.rbegin(); itm != models.rend(); itm++)
			{
				float3 size = (*itm)->getSize();
				(*itm)->setSize(size.x, height, size.z);
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
		vector<CartesianVector>::const_iterator it2;
		for (it2 = it1 + 1; it2 != vertexes.end() && !object.IsInCollision(
				*it1, *it2); it1 = it2, ++it2)
		{
			// Bloc vide
		}
		return it2 != vertexes.end();
	}
}

Wall::Wall(const CartesianVector& origin, const CartesianVector& direction,
		float userBaseHeight) :
	vertexes(1, origin), models(), xDirection(fabs(direction.x) > fabs(
			direction.z)), baseHeight(userBaseHeight), height(userBaseHeight)
{
	AddVertex();
}

