// Displayer.h
// D�finition de la classe Displayer
/*
#include "singleton.h"
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
	// DrawPlane, AddPlane
	// Pour plus tard, mesh

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
	Camera* camera;    // Temporaire
	Model* model;      // Temporaire
	Font* font;        // Temporaire
};
*/