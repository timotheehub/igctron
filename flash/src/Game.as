package  
{
	import flash.display.Stage;
	import flash.errors.IOError;
	
	/**
	 * ...
	 * @author Goost
	 */
	public class Game
	{
		public  var MAX_PLAYERS : int = 4;
		
		public  var ia : IA;
		
		//private var players : Array = new Array ();
		private var players : Vector.<Player> = new Vector.<Player>();
		
		//private var walls : Array = new Array ();
		private var walls : Vector.<Wall> = new Vector.<Wall>();
	
		public var stage : Stage;
		
		public function Game ( _stage : Stage ) 
		{
			stage = _stage;
		}
		
		public function getPlayerCount () : int
		{
			return players.length;
		}
		
		public function getPlayer (id : int) : Player
		{
			return players [id];
		}
		
		public function addPlayer (new_player : Player) : void
		{
			players.push ( new_player );
			/*create a new player*/
			
			walls.push ( new Wall( new_player ) );
			/*create a new wall and tells the wall who is its player*/
		}
		
		public function getWallCount () : int
		{
			return walls.length;
		}
		
		public function getWall (id : int) : Wall
		{
			return walls[id];
		}
		
		public function addWall (new_wall : Wall) : void
		{
			walls.push (new_wall);
		}
		
		public function check_collision (x0 : Number, y0 : Number, x1 : Number, y1 : Number, idPlayer : Number) : Boolean
		{ /* where (x0, y0) is the top left hand corner point and (x1, y1) the bottom right hand corner point */
		
			var collision : Boolean = false;
			var p : Player = Player(players[idPlayer]);
			
			for (var i : int = 0; i < walls.length; i++)
			{
				// if not Dead
				if ((!p.getLife()) && (collision = walls[i].checkWallCollision (x0, y0, x1, y1, idPlayer, i)))
				{
					break;
				}
			}
			
			if (!collision)
			{
				var x : Number = p.getCoord () [Player.X];
				var y : Number = p.getCoord () [Player.Y];
				var x1 : Number;
				var y1 : Number;
				var width : int;
				
				
				for ( var j : int = 0; j < players.length; j++)
				{
					if ((!players[j].getLife()) && j != idPlayer)
					{
						x1 = players[j].getCoord()[Player.X];
						y1 = players[j].getCoord()[Player.Y];
						width = (players[j].getVehicle()).getWidth(); 
						
						//TODO gestion véhicules non carrés à ajouter
						if ((Math.abs (x -  x1)  < (p.getVehicle()).getWidth()/2 + width/2) 
									&& (Math.abs (y - y1) < (p.getVehicle()).getWidth()/2 + width/2))
						{
							collision = true;
							break;
						}
						
					}
				}
			}
	
			return collision;
					
		}
		
		public function update() : void
		{
			for (var i : int = 0; i < players.length; i++)
			{
				players[i].update ();
			}
		}
		
	}

}