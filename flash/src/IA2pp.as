package  
{
	
	//import org.papervision3d.core.culling.ITriangleCuller;
	/**
	 * ...
	 * @author ben
	 */
	public class IA2pp extends IA2
	{
		// + IA features
		protected static const CHECK_PITCH:int = 3;		
		protected static const RAISE_VISI_CHECK:int = 15;
		protected static const BOOST_PERCENT:uint = 1;
		
		protected var last_visi_check:int = VISIBILITY; // last visibility used to check faster
		
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
			//var choixDir : Array = new Array (0,0,0,0);
			//var newDir : int = direction;
			
			if ( Math.round(Math.random()*100) <= BOOST_PERCENT )
			{
				player.useBooster();
			}
			
			if (  ( timer == 0 )&&( checkCollision(x, y, direction) || ( Math.round(Math.random()*100) <= TURN_PERCENT ))  )
			{
				direction = Player.convertDirection( best_direction(x, y, lastDirection, (last_visi_check+RAISE_VISI_CHECK) ) );
				
				if ( direction != lastDirection )
				{
					timer = NO_TURN;
					player.getWall().insertSegment( x, y, x, y );
				}
				
			}
			
			(timer > 0)? timer-- : timer;
			
			
			return direction;
		}
		
		protected function best_direction( x:Number, y:Number, dir:int, _visi:int = VISIBILITY ) : int
		{
			var dir_tested:int; // tested direction
			var rand_test:Number; // associate random value
			
			var current_dir:int = dir; // current best direction
			var rand_cur:Number = 0; // associate random value
			var found:Boolean=false;
			
			var visi:int = _visi; // tested visibility 
			
			
			while ( (visi - 10) > 0 )
			{
				for ( var i:int = -1; i < 2; i++ )
				{
					dir_tested = Player.convertDirection( dir + i );
					
					if ( !checkCollision(x, y, dir_tested, visi) )
					{ 	
						rand_test = Math.random();
						if ( rand_cur < rand_test )
						{
							rand_cur = rand_test;
							current_dir = dir_tested;
							found = true;
						}
					}
				}
				
				if (found)
				{
					break;
				}
				
				visi -= CHECK_PITCH;
			}
			
			last_visi_check = visi;
			
			return current_dir;
			
		}
		
	}

}