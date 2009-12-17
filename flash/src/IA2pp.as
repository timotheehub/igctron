package  
{
	/**
	 * ...
	 * @author ben
	 */
	public class IA2pp extends IA2
	{
		
		override public function IA2pp(  _player:Player, _id:int  ) 
		{
			super(_player, _id);
		}
		
		override public function update() : int
		{
			var direction:int = player.getDir();
			var x:Number = player.getCoord()[Player.X];
			var y:Number = player.getCoord()[Player.Y];
			
			
			
			if (  ( timer == 0 )&&( checkCollision(x, y, direction) || ( Math.round(Math.random()*100) <= TURN_PERCENT ))  )
			{
				
				timer = NO_TURN;
				
				( Math.random() >= 0.5 ) ? direction++: direction-- ;
				
				direction = Player.convertDirection(direction);
				
				if ( checkCollision(x, y, direction) )
				{
					direction += 2;
					direction = Player.convertDirection(direction);
					
				}				
				
				if ( ! checkCollision(x, y, direction) )
				{
					player.getWall().insertSegment( x, y, x, y );
				}
				

			}
			
			(timer > 0)? timer-- : timer;
			
			
			return direction;
		}
	}

}