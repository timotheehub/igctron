// Singleton.h
// Déclaration de la classe Singleton

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template <typename T>
class Singleton
{
public:
    // Renvoi l'instance du singleton
	static T *GetInstance ()
	{
		if ( theSingleton == 0 )
		{
			theSingleton = new T;
		}
		return ( static_cast<T*> ( theSingleton ) );
	}

	// Supprime le singleton
	static void kill ()
	{
		if ( theSingleton != 0 )
		{
			delete theSingleton;
			theSingleton = 0;
		}
	}

protected:
	// Constructeur
	Singleton () { }
	// Destructeur
	~Singleton () { }

private:
	static T *theSingleton; // Instance unique statique
};


template <typename T>
T *Singleton<T>::theSingleton = 0;

#endif // __SINGLETON_H__
