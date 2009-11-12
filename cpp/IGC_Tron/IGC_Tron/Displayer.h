// Displayer.h
// D�finition de la classe Displayer

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

using namespace IGC;

class Displayer : public Singleton<Displayer>
{
  friend class Singleton<Displayer>;

public:
	// Charge les ressources
	void LoadRessources ( );

	// Affiche l'�cran
	void InitScreen ( );

	// Rafra�chit graphiquement
	void UpdateGraphics ( );

	// Lib�re la m�moire
	void FreeMemory ( );

	// AddPlane, AddMoto
	// DrawPlane, DrawMoto
	// Pour plus tard, AddMesh
	void LoadScene ( );
	void UnloadScene ( );
	
	static void OnClose ( );
	static bool GetRunning ( );
	static void SetRunning ( bool isRunning );



private:
	// Constructeur
	Displayer ( );

	// Destructeur
	~Displayer ( );

	// M�thodes pour InitScreen
	void initEngine ( );
	void initWindow ( );	
	void initRenderer ( );

	// M�thodes pour FreeMemory
	void freeRenderer ( );
	void freeWindow ( );
	void freeEngine ( );

	// Attributs pour le moteur 3D
	Engine* engine;
	Factory* factory;
	IGC::Window* window;
	Renderer* renderer;
	Camera *camera;
	Model* model;
	IGC::Font* font;
	Texture *texture;

	static bool running;
};

#endif // __DISPLAYER_H__
