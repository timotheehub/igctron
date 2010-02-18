/*
 * Wall.h
 *
 *  Created on: 26 nov. 2009
 *      Author: fenrhil
 */

#ifndef WALL_H_
#define WALL_H_

#include <vector>
#include "Globals.h"
#include "IModel.h"
#include "D3DMaterial.h"
#include "OGLMaterial.h"

class Wall
{
public:
	void Init(const Utils::CartesianVector& origin);

	void Collapse(double dt); // Fait s'écrouler le mur un petit peu plus

	// Les deux méthodes suivantes ne doivent pas être appelées après
	// un appel à Collapse.
	// Pour pouvoir de nouveau les utiliser, appeler Init.
	void SetLastVertex(const Utils::CartesianVector& value);
	void AddVertex();

	void Draw() const;

	bool IsInCollision(const Utils::Rectangle& object) const;

	inline unsigned int GetVertexesCount ( );
	inline bool GetVertexe ( Utils::CartesianVector & cVector, const unsigned int i );

	Wall(const Utils::CartesianVector& origin,
			const Utils::CartesianVector& direction, float userBaseHeight);

protected:
	static const float BASE_HEIGHT;
	static const float COLLAPSE_RELATIVE_STEP;

	void addModel();
	void clear();

	std::vector<Utils::CartesianVector> vertexes;
	std::vector<IGC::Model*> models;
	bool xDirection;
	float baseHeight;
	float height;

	IGC::Material* material;
};

inline unsigned int Wall::GetVertexesCount ( )
{
	return vertexes.size ( );
}
inline bool Wall::GetVertexe ( Utils::CartesianVector & cVector, const unsigned int i )
{
	if ( i <= vertexes.size ( ) )
	{
		cVector = vertexes[i];
		return true;
	}
	else
	{
		return false;
	}
}


#endif /* WALL_H_ */
