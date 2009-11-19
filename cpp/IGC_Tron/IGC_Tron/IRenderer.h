/**************************************************************************/
/* This file is part of IGC Tron                                          */
/* (c) IGC Software 2009 - 2010                                           */
/* Author : Pierre-Yves GATOUILLAT                                        */
/**************************************************************************/
/* This program is free software: you can redistribute it and/or modify   */
/* it under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                    */
/*                                                                        */
/* This program is distributed in the hope that it will be useful,        */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/* GNU General Public License for more details.                           */
/*                                                                        */
/* You should have received a copy of the GNU General Public License      */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>.  */
/**************************************************************************/

#ifndef _RENDERER
#define _RENDERER

#ifdef _WIN32
	#pragma warning (disable : 4996)
#endif

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"

/***********************************************************************************/

namespace IGC
{
	class Engine;

	class IRenderer
	{

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	protected:

		Engine* engine;

		bool fullscreen; // vrai pour le mode plein �cran, faux pour le mode fen?tre

		bool verticalSync; // vrai pour activer la synchronisation verticale

		bool hardware; // vrai pour faire les rendus � l'aide de la carte graphique

		int width;
		int height;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie la classe et alloue la m�moire vid�o pour une surface de rendu dont la taille correspond �
			celle de la fen�tre associ�e � _engine.
		*/
		IRenderer( Engine* _engine );

		/*
			Lib�re la m�moire vid�o r�serv�e pour une surface de rendu.
		*/
		virtual ~IRenderer();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie un pointeur vers le moteur associ� � ce renderer.
		*/
		Engine* getEngine();

		/*
			Active le mode plein �cran et sp�cifie la r�solution � appliquer.
		*/
		void enableFullscreen( int _width, int _height );

		/*
			D�sactive le mode plein �cran.
		*/
		void disableFullscreen();

		/*
			Active la synchronisation du framerate avec le taux de rafraichissement vertical de l'�cran.
		*/
		void enableVSync();

		/*
			D?sactive la synchronisation verticale.
		*/
		void disableVSync();

		/*
			Active l'utilisation de la carte graphique pour le rendu final.
		*/
		void useHardware();

		/*
			D?sactive l'utilisation de la carte graphique pour le rendu final.
		*/
		void useSoftware();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Convertit une coordonn�e de point relatif ({0,0} �tant le coin sup�rieur gauche
			de l'�cran et {1,1} le coin inf�rieur droit) en coordonn�e absolue sur l'axe X.
		*/
		int toPointX( float _x );

		/*
			Convertit une coordonn�e de point relatif ({0,0} �tant le coin sup�rieur gauche
			de l'�cran et {1,1} le coin inf�rieur droit) en coordonn�e absolue sur l'axe Y.
		*/
		int toPointY( float _y );

		/*
			Initialise l'API et lui associe la surface de rendu.
		*/
		virtual void initialize() = 0;

		/*
			Lib�re toutes les ressources relatives � l'API.
		*/
		virtual void finalize() = 0;

		/*
			Active ou non la transparence pour le prochain rendu.
		*/
		virtual void setTransparency( bool _value ) = 0;

		/*
			Met � jour l'affichage en copiant le contenu du back buffer vers le frame buffer.
		*/
		virtual void update() = 0;

		/*
			Remplit le back buffer de la couleur sp�cifi�e et le depth buffer de la profondeur sp�cifi�e.
		*/
		virtual void clear( float _r = 0.0f, float _g = 0.0f, float _b = 0.0f, float _depth = 1.0f ) = 0;

		/*
			Affiche du texte � la position absolue sp�cifi�e avec la couleur sp�cifi�e en fonction de la police
			qui aura pr�c�demment �t� d�finie.
		*/
		virtual void drawText( const char* _text, int _x, int _y, float _r, float _g, float _b, float _a ) = 0;

		/*
			Affiche une image � la position absolue sp�cifi�e avec la couleur sp�cifi�e en fonction de la texture
			qui aura pr�c�demment �t� d�finie.
		*/
		virtual void drawImage( int _x0, int _y0, int _x1, int _y1,
									float _px = 0.0f, float _py = 0.0f, float _sx = 1.0f, float _sy = 1.0f,
											float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f ) = 0;

		/*
			 Redimensionne la scène.
		 */
		virtual void resizeScene ( int newWidth, int newHeight ) = 0;
	};
}

/***********************************************************************************/

#endif
