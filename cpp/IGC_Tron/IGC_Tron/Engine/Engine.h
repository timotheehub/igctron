
#ifndef _ENGINE
#define _ENGINE

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Common.h"
#include "IRenderer.h"
#include "IWindow.h"

/***********************************************************************************/

namespace IGC
{
	class Engine
	{

/***********************************************************************************/
/** CLASSES AMIES                                                                 **/
/***********************************************************************************/

		friend class IRenderer;
		friend class IWindow;

/***********************************************************************************/
/** ATTRIBUTS                                                                     **/
/***********************************************************************************/

	private:

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
		Engine()
			Instancie cette classe dont le but est de centraliser l'acc�s aux objets
			communs au module RT.
		*/
		Engine();

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

		/*
		getRenderer()
			Renvoie le renderer associ� � cette instance ou NULL si celui-ci n'a
			pas encore �t� cr��.
		*/
		IRenderer* getRenderer();

		/*
		getWindow()
			Renvoie la fen�tre associ�e � cette instance ou NULL si celle-ci n'a
			pas encore �t� cr��e.
		*/
		IWindow* getWindow();

		/*
		getTime()
			Renvoie le nombre de secondes �coul� depuis le d�marrage du syst�me.
		*/
		double getTime();

		/*
		getDelta()
			Renvoie le temps �coul� pour calculer et afficher la derni�re
			frame (en secondes)
		*/
		double getDelta();

		/*
		getCurrentFramerate()
			Renvoie le nombre de frames affich�es lors de la derni�re seconde.
		*/
		double getCurrentFramerate();

		/*
		getAverageFramerate()
			Renvoie le nombre moyen de frames affich�es par seconde depuis
			l'instanciation de cette classe.
		*/
		double getAverageFramerate();

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

		/*
		update()
			Met � jour l'ensemble des variables temporelles. Doit �tre appel�e une
			fois par frame.
		*/
		void update();

	};
}

/***********************************************************************************/

#endif
