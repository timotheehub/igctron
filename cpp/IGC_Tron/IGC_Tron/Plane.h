// Plane.h
// Declaration de la classe Plane

#ifndef __PLANE_H__
#define __PLANE_H__

class Plane
{
protected:
	int z;
	int x;

public:
	inline int GetZ ( ) const;
	inline int GetX ( ) const;
	void Draw ( );
	Plane ( int zValue = 30, int xValue = 20 );
	~Plane ( );
};

inline int Plane::GetZ ( ) const
{
	return z;
}

inline int Plane::GetX ( ) const
{
	return x;
}

#endif
