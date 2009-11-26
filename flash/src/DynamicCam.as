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
		
		private static const ZHEIGHT : int =  20;
		private static const BACK : int = + 60; 
		private static const V_ORBIT : int = 65;
		private static const PSI : int = +1; // 
		private static const ROT_SPEED : int = 2;
		private var width:Number;
		private var height:Number;
		private var h_orbit:Number;
		
		/**
		 * Constructor.
		 * 
		 * @param	fov		This value is the vertical Field Of View (FOV) in degrees.
		 * @param	near	Distance to the near clipping plane.
		 * @param	far		Distance to the far clipping plane.
		 * @param	useCulling		Boolean indicating whether to use frustum culling. When true all objects outside the view will be culled.
		 * @param	useProjection 	Boolean indicating whether to use a projection matrix for perspective.
		 */ 
		public function DynamicCam( _width:int, _height:int, _h_orbit:int=-90, fov:Number = 60, near:Number = 10, far:Number = 5000, useCulling:Boolean = false, useProjection:Boolean = false)
		{
			super(near, 40);
			width = _width;
			height = _height;
			h_orbit = _h_orbit;
			
			this.fov = fov; 
			
			_prevFocus = 0;
			_prevZoom = 0;
			_prevOrtho = false;
			_prevUseProjection = false;
			_useCulling = useCulling;
			_useProjectionMatrix = useProjection;
			_far = far;
			_focusFix = Matrix3D.IDENTITY;
			z = ZHEIGHT;
		}
		
		public function updateCam( cube : Cube, player : Player ) : void
		{
			var direction : int = player.getDir();
			var newX : Number;
			var newZ : Number;
			
			
			if( direction == Player.DIRECTION_LEFT )
			{
				h_orbit = h_orbit * ROT_SPEED / (ROT_SPEED+1);
				newX = cube.x + BACK;
				newZ = cube.y;
			}
			else if ( direction == Player.DIRECTION_RIGHT )
			{
				h_orbit = (180 + h_orbit * ROT_SPEED) / (ROT_SPEED +1);
				newX = cube.x - BACK;
				newZ = cube.y;
			}
			else if ( direction == Player.DIRECTION_DOWN  )
			{
				h_orbit = (90 + h_orbit * ROT_SPEED) / (ROT_SPEED+1);
				newX = cube.x;
				newZ = cube.y - BACK;
			}
			else if ( direction == Player.DIRECTION_UP )
			{
				h_orbit = (270 + h_orbit * ROT_SPEED) / (ROT_SPEED+1);	
				newX = cube.x;
				newZ = cube.y + BACK;
			}
			
			
			
			h_orbit = (h_orbit < 0)? -h_orbit : h_orbit;
			
			x = newX;
			y = ZHEIGHT;
			z = newZ;
			orbit( V_ORBIT, h_orbit, true, cube);
			zoom = 50;
			//this.lookAt( cube );
			//this.updateTransform();
			
			trace(h_orbit);
			//trace( distanceTo(cube));
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