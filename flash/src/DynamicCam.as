package  
{
	
	import org.papervision3d.cameras.Camera3D;
	import org.papervision3d.objects.primitives.Cube;
		
	/**
	 * ...
	 * @author ben
	 */
	public class DynamicCam extends Camera3D
	{
		
		private static const HEIGHT : int =  - 20;
		private static const BACK : int = + 60; 
		private static const V_ORBIT : int = 50;
		
		public function DynamicCam() 
		{
			z = HEIGHT;
		}
		
		public function updateCam( cube : Cube, player : Player ) : void
		{
			var direction : int = player.getDir();
			
			if( direction == Player.DIRECTION_LEFT )
			{
				x = cube.x - BACK;
				y = cube.y;
				orbit( V_ORBIT, 0, true, cube );				
			}
			else if ( direction == Player.DIRECTION_RIGHT )
			{
				x = cube.x + BACK;
				y = cube.y;
				orbit( V_ORBIT, 180, true, cube );
			}
			else if ( direction == Player.DIRECTION_DOWN  )
			{
				x = cube.x;
				y = cube.y + BACK;
				orbit( V_ORBIT, 90 , true, cube );
			}
			else if ( direction == Player.DIRECTION_UP )
			{
				x = cube.x;
				y = cube.y - BACK;
				orbit( V_ORBIT, -90 , true, cube );				
			}
			
			
		}
	}

}	

/*
			camere = new Camera3D();
			camere.z = -1000;
			camere.y = +200;
			//camere.x = +100;
			camere.zoom = 70;
			//camere.orbit( 50, -90, true, plane ); //-90
			*/