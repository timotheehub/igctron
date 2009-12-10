package  
{
	/**
	 * ...
	 * @author ben
	 */
	public class IA2
	{
	
		private var player : Player;
		private var id : int;
		private var timer : int;
		
		private static const VISIBILITY : int = 20;
		private static const TURN_PERCENT : int = 1;
		private static const NO_TURN :int = 10;
		
		public function IA2( _player:Player, _id:int ) 
		{
			player = _player;
			id = _id;		
			timer = 0;
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
		
		private function checkCollision( x:Number, y:Number, dir:int ) : Boolean
		{
			var x0:Number;
			var x1:Number;
			var y0:Number;
			var y1:Number;
			
			
			// ajouter gestion de la largeur
			if ( dir == Player.DIRECTION_LEFT )
			{
				y0 = y;
				y1 = y;
				x0 = x - VISIBILITY;
				x1 = x;
			}
			else if ( dir == Player.DIRECTION_DOWN )
			{
				y0 = y;
				y1 = y + VISIBILITY;
				x0 = x;
				x1 = x;
			}
			else if ( dir == Player.DIRECTION_RIGHT)
			{
				y0 = y;
				y1 = y;
				x0 = x;
				x1 = x + VISIBILITY;
			}
			else // UP
			{
				y0 = y - VISIBILITY;
				y1 = y;
				x0 = x;
				x1 = x;
			}
			
			return Main.game.check_collision( x0, y0, x1, y1, id);
			/* where (x0, y0) is the top left hand corner point and (x1, y1) the bottom right hand corner point */			
		}
	}

}