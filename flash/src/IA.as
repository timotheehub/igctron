package  
{
	
	public class IA
	{
		//Directions : Player.DIRECTION_<LEFT/DOWN/RIGHT/UP>
		private var players : Array = new Array ();
		private var walls : Array = new Array ();
		
		//Constantes de la matrice representant le plateau de jeu
		public static const VIDE : int = 0;
		public static const PLAYER : int = 1;
		public static const MUR : int = 2;
		public static const PLAYER_AND_WALL : int = 3; //Cas qui n'arrive jamais
		
		
		private var tab :Array; //Matrice tab[x][y]
		private var precision : Number = 0.01;
		 
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
			return calcul (direction, id);
		}
		
		private function calcul (direction : int, id : int) : int
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
						
			
			for (i = 0; i < players.length; i++)
			{
				/* Pour chaque pixel (j, k) de player (en tenant comptede la précision), 
				 * on fait tab[Math.round(j)][Math.round(k)] = IA.PLAYER;
				 */
				var ptmp:Player = players[i];
				var vtmp:Vehicle = ptmp.getVehicle();
				for (j = 0; j < vtmp.getWidth(); j += vtmp.getWidth() / precision)
				{
					for (k = 0; k < vtmp.getHeight(); k += vtmp.getHeight() / precision)
					{
						tab[(int)(Math.round(j) + ptmp.getCoord()[Player.X]*precision)]
							[(int)(Math.round(k) + ptmp.getCoord()[Player.Y]*precision)]
							= IA.PLAYER;
					}
				}
			}
			
			for (i = 0; i < walls.length; i++)
			{
				for (j = 0; j < walls[i].getSegmentCount(); j++)
				{
					var tmp:Segment = walls[i].getSegment(j);
					for (k = tmp.getXmin(); k < tmp.getXmax(); k += (tmp.getXmax() - tmp.getXmin()) / precision)
					{
						for (l = tmp.getYmin(); l < tmp.getYmax() ; l+= (tmp.getYmax() - tmp.getYmin()) / precision)
						{
							tab[Math.round(k)][Math.round(l)] = IA.MUR;
						}
					}
				}
			}
			
			//FIN DISCRETISATION
			
			//Fonction "en attendant"
			if (Math.random() > 0.9) //METTRE 1 POUR QUE L'IA NE TOURNE PAS
			{
				var modif:Number = (int)(Math.random() * 2);
				if (modif == 0)
				{
					direction++;
				} else if (modif == 1)
				{
					direction--;
				}
				direction = (direction < Player.DIRECTION_LEFT) ? Player.DIRECTION_UP : direction;
				direction = (direction > Player.DIRECTION_UP) ? Player.DIRECTION_LEFT : direction;
				
				var tmp2 : Player = players[id];
				tmp2.getWall().insertSegment( tmp2.getCoord()[Player.X], 
					tmp2.getCoord()[Player.Y], tmp2.getCoord()[Player.X], tmp2.getCoord()[Player.Y] );
			}
			
			return direction;
		}
		
	}

}
