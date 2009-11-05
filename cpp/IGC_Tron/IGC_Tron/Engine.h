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

#ifndef _ENGINE
#define _ENGINE

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"
#include "Factory.h"
#include "D3DRenderer.h"
#include "OGLRenderer.h"
#include "W32Window.h"
#include "X11Window.h"

/***********************************************************************************/

namespace IGC
{
	class Engine
	{

/***********************************************************************************/
/** CLASSES AMIES                                                                 **/
/***********************************************************************************/

		friend class Factory;

		friend class IRenderer;
		friend class IWindow;

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

		Factory* factory;

		IRenderer* renderer;
		IWindow* window;

		double frameTime;
		double cycleTime;
		double totalTime;
		double frameDelta;

		wide cycleCount;
		wide totalCount;

		double currentFramerate;
		double averageFramerate;

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	public:

		/*
			Instancie cette classe dont le but est de centraliser l'accès aux objets communs du moteur.
		*/
		Engine();

		/*
			Détruit la factory.
		*/
		~Engine();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie la factory associée à cette instance.
		*/
		Factory* getFactory();

		/*
			Renvoie le renderer associé à cette instance ou NULL si celui-ci n'a pas encore été créé.
		*/
		Renderer* getRenderer();

		/*
		getWindow()
			Renvoie la fenêtre associée à cette instance ou NULL si celle-ci n'a pas encore été créée.
		*/
		Window* getWindow();

		/*
			Renvoie le nombre de secondes écoulé depuis le démarrage du système.
		*/
		double getTime();

		/*
			Renvoie le temps écoulé pour calculer et afficher la dernière frame (en secondes)
		*/
		double getDelta();

		/*
			Renvoie le nombre de frames affichées lors de la dernière seconde.
		*/
		double getCurrentFramerate();

		/*
			Renvoie le nombre moyen de frames affichées par seconde depuis l'instanciation de cette classe.
		*/
		double getAverageFramerate();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Met à jour l'ensemble des variables temporelles. Doit être appelée une fois par frame.
		*/
		void update();

	};
}

/***********************************************************************************/

#endif
