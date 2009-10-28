
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

		bool fullscreen; // vrai pour le mode plein écran, faux pour le mode fenêtre

		bool verticalSync; // vrai pour activer la synchronisation verticale

		bool hardware; // vrai pour faire les rendus à l'aide de la carte graphique

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
		IRenderer( Engine* _engine )
			Instancie la classe et alloue la mémoire vidéo pour une surface de rendu
			dont la taille correspond à celle de la fenêtre associée à _engine.
		*/
		IRenderer( Engine* _engine );

		/*
		~IRenderer()
			Libère la mémoire vidéo réservée pour une surface de rendu.
		*/
		virtual ~IRenderer();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

		/*
		getEngine()
			Renvoie un pointeur vers le moteur associé à ce renderer.
		*/
		Engine* getEngine();

		/*
		enableFullscreen( int _width, int _height )
			Active le mode plein écran et spécifie la résolution à appliquer.
		*/
		void enableFullscreen( int _width, int _height );

		/*
		disableFullscreen()
			Désactive le mode plein écran.
		*/
		void disableFullscreen();

		/*
		enableVSync()
			Active la synchronisation du framerate avec le taux de rafraichissement vertical
			de l'écran.
		*/
		void enableVSync();

		/*
		disableVSync()
			Désactive la synchronisation verticale.
		*/
		void disableVSync();

		/*
		useHardware()
			Active l'utilisation de la carte graphique pour le rendu final.
		*/
		void useHardware();

		/*
		useSoftware()
			Désactive l'utilisation de la carte graphique pour le rendu final.
		*/
		void useSoftware();

		/*
		insertLabel()
			Ajoute un label à afficher au premier plan. Le texte à affiché est défini par le
			paramètre _text. Les paramètres _x et _y définissent la position en pixels de ce
			label. Enfin les paramètres _r, g_, _b, et _a définissent la couleur et la valeur
			de transparence du texte à afficher.
		*/
		void insertLabel( const string& _text, int _x, int _y,
			float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f );

		/*
		clearForeground()
			Supprime tous les éléments ajoutés au premier plan.
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
			Libère toutes les ressources relatives à l'API.
		*/
		virtual void finalize() = 0;

		/*
		update()
			Met à jour l'affichage en copiant le contenu du back buffer vers le frame buffer.
		*/
		virtual void update() = 0;

		virtual void clear( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _depth = 1.0f ) = 0;

	};
}

/***********************************************************************************/

#endif
