
#ifndef _RENDERER
#define _RENDERER

#pragma warning (disable : 4996)

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"
#include "ICamera.h"

#include <vector>
#include <string>

using namespace std;

/***********************************************************************************/

namespace IGC
{
	class Engine;
	class ICamera;

	class IRenderer
	{

/***********************************************************************************/
/** TYPES                                                                         **/
/***********************************************************************************/

	public:

		typedef struct
		{
			string text;
			int x, y;
			float r, g, b, a;
		} Label;

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		Engine* engine;

		vector<Label> labels;

		bool fullscreen; // vrai pour le mode plein �cran, faux pour le mode fen�tre

		bool verticalSync; // vrai pour activer la synchronisation verticale

		bool hardware; // vrai pour faire les rendus � l'aide de la carte graphique

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
		IRenderer( Engine* _engine )
			Instancie la classe et alloue la m�moire vid�o pour une surface de rendu
			dont la taille correspond � celle de la fen�tre associ�e � _engine.
		*/
		IRenderer( Engine* _engine );

		/*
		~IRenderer()
			Lib�re la m�moire vid�o r�serv�e pour une surface de rendu.
		*/
		virtual ~IRenderer();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

		/*
		getEngine()
			Renvoie un pointeur vers le moteur associ� � ce renderer.
		*/
		Engine* getEngine();

		/*
		enableFullscreen( int _width, int _height )
			Active le mode plein �cran et sp�cifie la r�solution � appliquer.
		*/
		void enableFullscreen( int _width, int _height );

		/*
		disableFullscreen()
			D�sactive le mode plein �cran.
		*/
		void disableFullscreen();

		/*
		enableVSync()
			Active la synchronisation du framerate avec le taux de rafraichissement vertical
			de l'�cran.
		*/
		void enableVSync();

		/*
		disableVSync()
			D�sactive la synchronisation verticale.
		*/
		void disableVSync();

		/*
		useHardware()
			Active l'utilisation de la carte graphique pour le rendu final.
		*/
		void useHardware();

		/*
		useSoftware()
			D�sactive l'utilisation de la carte graphique pour le rendu final.
		*/
		void useSoftware();

		/*
		insertLabel()
			Ajoute un label � afficher au premier plan. Le texte � affich� est d�fini par le
			param�tre _text. Les param�tres _x et _y d�finissent la position en pixels de ce
			label. Enfin les param�tres _r, g_, _b, et _a d�finissent la couleur et la valeur
			de transparence du texte � afficher.
		*/
		void insertLabel( const string& _text, int _x, int _y,
			float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f );

		/*
		clearForeground()
			Supprime tous les �l�ments ajout�s au premier plan.
		*/
		void clearForeground();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

		/*
		initialize()
			Initialise l'API et lui associe la surface de rendu.
		*/
		virtual void initialize() = 0;

		/*
		finalize()
			Lib�re toutes les ressources relatives � l'API.
		*/
		virtual void finalize() = 0;

		/*
		update()
			Met � jour l'affichage en copiant le contenu du back buffer vers le frame buffer.
		*/
		virtual void update() = 0;

		virtual void clear( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _depth = 1.0f ) = 0;

	};
}

/***********************************************************************************/

#endif
