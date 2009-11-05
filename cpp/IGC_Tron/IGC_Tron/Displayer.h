// Displayer.h
// Définition de la classe Displayer
/*
#include "singleton.h"
using namespace IGC;

class Displayer : public Singleton<Displayer>
{
  friend class Singleton<Displayer>;

public:
	// Charge les ressources
	void LoadRessources ( );

	// Affiche l'écran
	void InitScreen ( );

	// Rafraîchit graphiquement
	void UpdateGraphics ( );

	// Libère la mémoire
	void FreeMemory ( );

	// AddPlane, AddMoto
	// DrawPlane, AddPlane
	// Pour plus tard, mesh

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
	Engine* engine;
	Factory* factory;
	Window* window;
	Renderer* renderer;
	Camera* camera;    // Temporaire
	Model* model;      // Temporaire
	Font* font;        // Temporaire
};
*/