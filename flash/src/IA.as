package  
{
	
	public class IA
	{
		//Directions : Player.DIRECTION_<LEFT/DOWN/RIGHT/UP>
		private var players : Array = new Array ();
		private var walls : Array = new Array ();
		
		//Constantes de la matrice representant le plateau de jeu
		private const VIDE : int = 0;
		private const PLAYER :int = 1;
		private const MUR :int = 2;
		private const PLAYER_AND_WALL :int = 3; //Cas qui n'arrive jamais
		
		
		private var tab :Array;
		private var precision : Number;
		 
		public function IA() 
		{
			var i : int;
			var nPlayers : int = Main.game.getPlayerCount ();
			var nWalls : int = Main.game.getWallCount ();
			
			for (i = 0; i < nPlayers; i++)
			{
				players [i] = Main.game.getPlayer (i);
			}
			
			for (i = 0; i < nWalls; i++)
			{
				walls [i] = Main.game.getWall (i);
			}
		}
		
		public function update(direction : int, id : int) : int 
		{
			
			
			
			return direction;
		}
		
		private function calcul () : void
		{
			var i : int;
			
			//DISCRETISATION DU PROBLEME
			tab = new Array();
			
			for (i = 0; i < Main.PLANE_WIDTH * precision; i++)
			{
				tab[i] = new Array();
				for (var j:int = 0; j < Main.PLANE_HEIGHT * precision; j++)
				{
					//fonction de discrétisation :D
				}
			}
			
			//ici on a un tab qui contient une matrice du plateau de jeu
			
		}
		
	}

}
