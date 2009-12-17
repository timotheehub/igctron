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
};

#endif /* WALL_H_ */
