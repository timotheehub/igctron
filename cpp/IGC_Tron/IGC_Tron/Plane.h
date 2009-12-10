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
	inline int GetWidth ( );
	inline int GetHeight ( );
	void Draw ( );
	Plane ( int aWidth = 30, int aHeight = 20 );
	~Plane ( );
};

inline int Plane::GetWidth ( )
{
	return width;
}

inline int Plane::GetHeight ( )
{
	return height;
}

#endif