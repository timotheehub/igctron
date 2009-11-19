package  
{
	
	import org.papervision3d.cameras.Camera3D;
	import org.papervision3d.objects.primitives.Cube;
	import org.papervision3d.core.math.Matrix3D;
		
	/**
	 * ...
	 * @author ben
	 */
	public class DynamicCam extends Camera3D
	{
		
		private static const HEIGHT : int =  - 20;
		private static const BACK : int = + 60; 
		private static const V_ORBIT : int = 50;
		private static const PSI : int = -5;
				
		/**
		 * Constructor.
		 * 
		 * @param	fov		This value is the vertical Field Of View (FOV) in degrees.
		 * @param	near	Distance to the near clipping plane.
		 * @param	far		Distance to the far clipping plane.
		 * @param	useCulling		Boolean indicating whether to use frustum culling. When true all objects outside the view will be culled.
		 * @param	useProjection 	Boolean indicating whether to use a projection matrix for perspective.
		 */ 
		public function DynamicCam(fov:Number=60, near:Number=10, far:Number=5000, useCulling:Boolean=false, useProjection:Boolean=false)
		{
			super(near, 40);
			
			this.fov = fov; 
			
			_prevFocus = 0;
			_prevZoom = 0;
			_prevOrtho = false;
			_prevUseProjection = false;
			_useCulling = useCulling;
			_useProjectionMatrix = useProjection;
			_far = far;
			_focusFix = Matrix3D.IDENTITY;
			z = HEIGHT;
		}
		
		public function updateCam( cube : Cube, player : Player ) : void
		{
			var direction : int = player.getDir();
			
			if( direction == Player.DIRECTION_LEFT )
			{
				//x = cube.x - BACK;
				//y = cube.y;
				orbit( V_ORBIT, 0+PSI, true, cube );	
			}
			else if ( direction == Player.DIRECTION_RIGHT )
			{
				//x = cube.x + BACK;
				//y = cube.y;
				orbit( V_ORBIT, 180+PSI, true, cube );
			}
			else if ( direction == Player.DIRECTION_DOWN  )
			{
				//x = cube.x;
				//y = cube.y + BACK;
				orbit( V_ORBIT, 90+PSI , true, cube );
			}
			else if ( direction == Player.DIRECTION_UP )
			{
				//x = cube.x;
				//y = cube.y - BACK;
				orbit( V_ORBIT, -90+PSI , true, cube );	
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