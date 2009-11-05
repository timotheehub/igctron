package  
{
	import flash.errors.IOError;
	/**
	 * ...
	 * @author Goost
	 */
	public class Game
	{
		private var MAX_PLAYERS : int = 4;
		
		private var players : Array = new Array (0);
		private var walls : Array = new Array (0);
		
		public function Game () 
		{
			for (var i : int = 0; i < players.length; i++)
			{
				players [i].update ();
			}
		}
		
		public function getplayercount (void) : int
		{
			return players.length;
		}
		
		public function getplayer (id : int) : Player
		{
			return players [id];
		}
		
		public function addplayer (new_player : Player) : void
		{
			players.push ();
			players [players.length - 1] = new_player;
			/*create a new player*/
			
			walls.push ();
			walls [walls.length - 1].Wall (new_player);
			/*create a new wall and tells the wall who is its player*/
		}
		
		public function getwallcount (void) : int
		{
			return walls.length;
		}
		
		public function getwall (id : int) : Wall
		{
			return walls [id];
		}
		
		public function addwall (new_wall : Wall) : void
		{
			walls.push (new_wall);
		}
		
		public function check_collision (x0 : Number, y0 : Number, x1 : Number, y1 : Number) : Boolean
		{ /* where (x0, y0) is the top left hand corner point and (x1, y1) the bottom right hand corner point */
		
			var collision : Boolean = false;
			
			for (var i : int = 0; i < walls.length; i++)
			{
				if ((collision = walls [i].CheckWallCollision (x0, y0, x1, y1)))
				{
					break;
				}
			}
			
			return collision;
					
		}
		
	}

}