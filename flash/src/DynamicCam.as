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
		private static const BACK : int = + 70; 
		private static const V_ORBIT : int = 65;
		private static const PSI : int = 3; // required to see wall (thickness = 0) when cam. just behind
		private static const ROT_SPEED : int = 10;
		private static const ZOOM : int = 70;
		private var width:Number;
		private var height:Number;
		private var h_orbit:Number;
		private var last_angle:Number;
		
		/**
		 * Constructor.
		 * 
		 * @param	fov		This value is the vertical Field Of View (FOV) in degrees.
		 * @param	near	Distance to the near clipping plane.
		 * @param	far		Distance to the far clipping plane.
		 * @param	useCulling		Boolean indicating whether to use frustum culling. When true all objects outside the view will be culled.
		 * @param	useProjection 	Boolean indicating whether to use a projection matrix for perspective.
		 */ 
		
		public function DynamicCam( _width:int, _height:int, _h_orbit:int=270, fov:Number = 60, near:Number = 10, far:Number = 5000, useCulling:Boolean = false, useProjection:Boolean = false)
		{
			super(near, 40);
			width = _width;
			height = _height;
			h_orbit = _h_orbit; // default : direction UP
			last_angle = h_orbit;
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
			
			zoom = ZOOM;
		}
		
		public function updateCam( cube : Cube, player : Player ) : void
		{
			var direction : int = player.getDir();
			var newX : Number;
			var newZ : Number;
			var k : int = (h_orbit - h_orbit%360) / 360;
			
			
			if( direction == Player.DIRECTION_LEFT )
			{
				last_angle = next_angle(0);
				newX = cube.x + BACK;
				newZ = cube.y;
			}
			else if ( direction == Player.DIRECTION_RIGHT )
			{
				last_angle = next_angle(180);
				newX = cube.x - BACK;
				newZ = cube.y;
			}
			else if ( direction == Player.DIRECTION_DOWN  )
			{
				last_angle = next_angle(90);
				newX = cube.x;
				newZ = cube.y - BACK;
			}
			else if ( direction == Player.DIRECTION_UP )
			{
				last_angle = next_angle(270);
				newX = cube.x;
				newZ = cube.y + BACK;
			}
			
			h_orbit = ( last_angle + h_orbit * ROT_SPEED) / (ROT_SPEED +1);
			
			x = newX;
			y = ZHEIGHT;
			z = newZ;
			orbit( V_ORBIT, h_orbit + PSI, true, cube);
			
			
		}
		
		
		private function next_angle( fixed_angle : int ) : Number
		{				
			var modulo : Number = (h_orbit - fixed_angle) % 360;
			var temp : Number = (modulo < 180) ? (h_orbit - modulo) : (h_orbit + modulo )
			
			if ( last_angle%360 != fixed_angle)
			{
				switch (fixed_angle)
				{
					case 0 : 
					{ return ( last_angle%360 == 90 )? ( last_angle - 90) : ( last_angle + 90 ); }
					
					case 90 : 
					{ return ( last_angle%360 == 180 )? ( last_angle - 90) : ( last_angle + 90 ); }
					
					case 180 :
					{ return ( last_angle%360 == 270 )? ( last_angle - 90) : ( last_angle + 90 ); }
					
					case 270 :
					{ return ( last_angle%360 == 0 )? ( last_angle - 90) : ( last_angle + 90 ); }
					
					default : 
					return 0;
				}
			}
			else
			{ return last_angle;}
			
		}
		
	}
}	



