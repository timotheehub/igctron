package  
{
	/**
	 * ...
	 * @author ben
	 */
	public class IA2
	{
	
		protected var player : Player;
		protected var id : int;
		protected var timer : int;
		
		protected var width:Number;
		protected var heigth:Number;
		
		// IA features
		protected static const VISIBILITY : int = 50; // range of frontal collision check
		protected static const TURN_PERCENT : uint = 1; // random percent -> turn
		protected static const NO_TURN : uint = 5; // number of frames before be alowed to turn after a turn
		
		public function IA2( _player:Player, _id:int ) 
		{
			player = _player;
			id = _id;
			timer = 0;
			
			width = (player.getVehicle()).getWidth();
			heigth = (player.getVehicle()).getHeight();
			
		}
		
		
		public function update() : int
		{
			var direction:int = player.getDir();
			var x:Number = player.getCoord()[Player.X];
			var y:Number = player.getCoord()[Player.Y];
			
			
			
			if (  ( timer == 0 )&&( checkCollision(x, y, direction) || ( Math.round(Math.random()*100) <= TURN_PERCENT ))  )
			{
				timer = NO_TURN;
				
				( Math.random() >= 0.5 ) ? direction++: direction-- ;
				
				direction = (direction < Player.DIRECTION_LEFT) ? Player.DIRECTION_UP : direction;
				direction = (direction > Player.DIRECTION_UP) ? Player.DIRECTION_LEFT : direction;
				
				player.getWall().insertSegment( x, y, x, y );

			}
			
			(timer > 0)? timer-- : timer;
			
			
			return direction;
		}
		
		protected function checkCollision( x:Number, y:Number, dir:int, visi:int=VISIBILITY) : Boolean
		{
			var x0:Number;
			var x1:Number;
			var y0:Number;
			var y1:Number;
			
			// ajouter gestion de la hauteur
			if ( dir == Player.DIRECTION_LEFT )
			{
				y0 = y - width;
				y1 = y + width;
				x0 = x - visi;
				x1 = x;
			}
			else if ( dir == Player.DIRECTION_DOWN )
			{
				y0 = y;
				y1 = y + visi;
				x0 = x -  width;
				x1 = x +  width;
			}
			else if ( dir == Player.DIRECTION_RIGHT)
			{
				y0 = y - width;
				y1 = y + width;
				x0 = x;
				x1 = x + visi;
			}
			else // UP
			{
				y0 = y - visi;
				y1 = y;
				x0 = x - width;
				x1 = x + width;
			}
			
			return Main.game.check_collision( x0, y0, x1, y1, id);
			/* where (x0, y0) is the top left hand corner point and (x1, y1) the bottom right hand corner point */			
		}
	}

}