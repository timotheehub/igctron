// Singleton.h
// Déclaration de la classe Singleton

template <typename T>
class Singleton
{
public:
    // Renvoi l'instance du singleton
	static T *getInstance ()
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
			theSingleton = NULL;
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
