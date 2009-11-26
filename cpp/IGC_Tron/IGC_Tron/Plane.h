// Plane.h
// Déclaration de la classe Plane

#ifndef __PLANE_H__
#define __PLANE_H__

class Plane
{
protected:
	int width;
	int height;

public:
	void Draw ( );
	Plane ( int aWidth = 30, int aHeight = 20 );
	~Plane ( );
};

#endif