package  
{
	
	public class IA
	{
		//Directions : Player.DIRECTION_<LEFT/DOWN/RIGHT/UP>
		private var players : Array = new Array ();
		private var walls : Array = new Array ();
		
		//Constantes de la matrice representant le plateau de jeu
		private const VIDE : int = 0;
		private const PLAYER : int = 1;
		private const MUR : int = 2;
		private const PLAYER_AND_WALL : int = 3; //Cas qui n'arrive jamais
		
		
		private var tab :Array;
		private var precision : Number;
		 
		public function IA() : void
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
			
			
			
			return calcul ();
		}
		
		private function calcul () : int
		{
			var i : int;
			var j : int;
			var k : int;
			var l : int;
			
			//DISCRETISATION DU PROBLEME
			tab = new Array();
			
			for (i = 0; i < Main.PLANE_WIDTH * precision; i++)
			{
				tab[i] = new Array();
				for (j = 0; j < Main.PLANE_HEIGHT * precision; j++)
				{
					tab[i][j] = 0;
				}
			}
			
			
			for (i = 0; i < players.length; i++) {
				/* Pour chaque pixel (j, k) de player (en tenant comptede la précision), 
				 * on fait tab[Math.round(j)][Math.round(k)] = PLAYER;
				 */
			}
			
			for (i = 0; i < walls.length; i++) {
				for (j = 0; j < walls[i].getSegmentCount(); j++) {
					/* Pour chaque pixel (k, l) de player (en tenant comptede la précision), 
					* on fait tab[Math.round(k)][Math.round(l)] = MUR;
					*/
				}
			}
			
			return Math.random () * 2;
			
		}
		
	}

}
