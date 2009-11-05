// Displayer.h
// D�finition de la classe Displayer

#ifndef __DISPLAYER_H__
#define __DISPLAYER_H__

#include "Singleton.h"

#include "Common.h"
#include "Engine.h"
#include "W32Window.h"
#include "X11Window.h"
#include "D3DRenderer.h"
#include "D3DCamera.h"
#include "D3DMesh.h"
#include "D3DModel.h"
#include "D3DFont.h"
#include "OGLRenderer.h"
#include "OGLCamera.h"
#include "OGLMesh.h"
#include "OGLModel.h"
#include "OGLFont.h"

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
	
	bool running;

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
	Window* window;
	Renderer* renderer;
	Camera *camera;
	Model* model;
	Font* font;
};

#endif // __DISPLAYER_H__