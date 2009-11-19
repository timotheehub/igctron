package  
{
	
	public class IA
	{
		//Directions : Player.DIRECTION_<LEFT/DOWN/RIGHT/UP>
		
		//Constantes de la matrice representant le plateau de jeu
		private const VIDE = 0;
		private const PLAYER = 1;
		private const MUR = 2;
		private const PLAYER_AND_WALL = 3; //Cas qui n'arrive jamais
		
		
		private var tab :Array;
		private var precision : Number;
		 
		public function IA() 
		{
			
		}
		
		public function update(direction : int, wall : Wall) : int 
		{
			
			return 0;
		}
		
		private function calcul () : void
		{
			//Discretisation du probleme
			tab = new Array();
			for (var i:int = 0; i < Main.PLANE_WIDTH * precision; i++)
			{
				tab[i] = new Array();
			}
			
			for (var i:int = 0; i < Main.PLANE_WIDTH * precision; i++)
			{
				for (var j:int = 0; j < Main.PLANE_HEIGHT * precision; j++)
				{
					//On cherche à savoir ce qui se trouve sur cette case
					if(
					tab[i][j];
				}
			}
			
		}
		
	}

}
