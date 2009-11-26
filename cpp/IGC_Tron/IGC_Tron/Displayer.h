// Displayer.h
// Déclaration de la classe Displayer

#ifndef __DISPLAYER_H__
#define __DISPLAYER_H__

#include "Singleton.h"

#include "Common.h"
#include "Engine.h"
#include "Factory.h"
#include "W32Window.h"
#include "X11Window.h"
#include "D3DRenderer.h"
#include "D3DCamera.h"
#include "D3DMesh.h"
#include "D3DModel.h"
#include "D3DFont.h"
#include "D3DTexture.h"
#include "OGLRenderer.h"
#include "OGLCamera.h"
#include "OGLMesh.h"
#include "OGLModel.h"
#include "OGLFont.h"
#include "OGLTexture.h"

using namespace std;
using namespace IGC;

class Displayer : public Singleton<Displayer>
{
  friend class Singleton<Displayer>;

public:
	// Types
	enum StateEnum { MENU, GAME };

	// Charge les ressources
	void LoadRessources ( );

	// Affiche l'écran
	void InitScreen ( );

	// Rafraîchit graphiquement
	void UpdateGraphics ( );

	// Libère la mémoire
	void FreeMemory ( );

	// AddPlane, AddMoto
	// DrawPlane, DrawMoto
	// Pour plus tard, AddMesh
	void LoadScene ( );
	void UnloadScene ( );

	void RegisterKeys( IGC::IWindow::LPKEYDOWNCALLBACK _cbKeyDown,
					IGC::IWindow::LPKEYUPCALLBACK _cbKeyUp );
	void UnregisterKeys( IGC::IWindow::LPKEYDOWNCALLBACK _cbKeyDown,
					IGC::IWindow::LPKEYUPCALLBACK _cbKeyUp );
	
	double GetTime ( );

	StateEnum GetState ( );
	void SetState ( StateEnum aState );

	inline IGC::Engine* GetEngine ( );
	inline IGC::Factory* GetFactory ( );
	inline IGC::Renderer* GetRenderer ( );
	inline IGC::Window* GetWindow ( );
	
	static void OnClose ( );
	static bool GetRunning ( );
	static void SetRunning ( bool isRunning );


protected:
	void DrawFps ( );

private:
	// Constructeur
	Displayer ( );

	// Destructeur
	~Displayer ( );

	// Méthodes pour InitScreen
	void initEngine ( );
	void initWindow ( );	
	void initRenderer ( );

	// Méthodes pour FreeMemory
	void freeRenderer ( );
	void freeWindow ( );
	void freeEngine ( );

	// Attributs pour le moteur 3D
	IGC::Engine* engine;
	IGC::Factory* factory;
	IGC::Window* window;
	IGC::Renderer* renderer;

	// Variable d'etat
	StateEnum state;

	// Attributs statiques
	static bool running;
};

/******************************************************************************
*                              Accesseurs                                     *
******************************************************************************/
inline IGC::Engine* Displayer::GetEngine ( )
{
	return engine;
}

inline IGC::Factory* Displayer::GetFactory ( )
{
	return factory;
}

inline IGC::Renderer* Displayer::GetRenderer ( )
{
	return renderer;
}

inline IGC::Window* Displayer::GetWindow ( )
{
	return window;
}

#endif // __DISPLAYER_H__