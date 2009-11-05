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
#include "D3DRenderer.h"
#include "OGLRenderer.h"
#include "W32Window.h"
#include "X11Window.h"

/***********************************************************************************/

namespace IGC
{
	class Factory;

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
			Instancie cette classe dont le but est de centraliser l'acc�s aux objets communs du moteur.
		*/
		Engine();

		/*
			D�truit la factory.
		*/
		~Engine();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	public:

		/*
			Renvoie la factory associ�e � cette instance.
		*/
		Factory* getFactory();

		/*
			Renvoie le renderer associ� � cette instance ou NULL si celui-ci n'a pas encore �t� cr��.
		*/
		Renderer* getRenderer();

		/*
		getWindow()
			Renvoie la fen�tre associ�e � cette instance ou NULL si celle-ci n'a pas encore �t� cr��e.
		*/
		Window* getWindow();

		/*
			Renvoie le nombre de secondes �coul� depuis le d�marrage du syst�me.
		*/
		double getTime();

		/*
			Renvoie le temps �coul� pour calculer et afficher la derni�re frame (en secondes)
		*/
		double getDelta();

		/*
			Renvoie le nombre de frames affich�es lors de la derni�re seconde.
		*/
		double getCurrentFramerate();

		/*
			Renvoie le nombre moyen de frames affich�es par seconde depuis l'instanciation de cette classe.
		*/
		double getAverageFramerate();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	public:

		/*
			Met � jour l'ensemble des variables temporelles. Doit �tre appel�e une fois par frame.
		*/
		void update();

	};
}

/***********************************************************************************/

#endif
