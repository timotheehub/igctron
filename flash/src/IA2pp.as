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
			var lastDirection:int = player.getDir();
			var direction : int = lastDirection;
			var x:Number = player.getCoord()[Player.X];
			var y:Number = player.getCoord()[Player.Y];
			var choixDir : Array = new Array (0,0,0,0);
			var newDir : int = 0;
			
			if (  ( timer == 0 )&&( checkCollision(x, y, direction) || ( Math.round(Math.random()*100) <= TURN_PERCENT ))  )
			{
				
				timer = NO_TURN;
				
				/*( Math.random() >= 0.5 ) ? direction++: direction-- ;
				
				direction = Player.convertDirection(direction);*/
				for (var i : int = 0; i < 4; i++)
				{
					if (!checkCollision(x, y, direction) && direction != Player.convertDirection(lastDirection + 2))
					{
						choixDir [direction] = Math.random ();
						if (choixDir [direction] > choixDir [newDir])
						{
							newDir = direction;
						}
					}	
					direction++;
					direction = Player.convertDirection(direction);
				}
				
				if ( ! checkCollision(x, y, direction) )
				{
					player.getWall().insertSegment( x, y, x, y );
				}
				

			}
			
			(timer > 0)? timer-- : timer;
			
			
			return newDir;
		}
	}

}