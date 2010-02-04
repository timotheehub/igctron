package  
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import org.papervision3d.core.geom.TriangleMesh3D;
	import org.papervision3d.objects.primitives.Cube;
	import org.papervision3d.objects.primitives.Plane;
	
	public class Player
	{
		public static const KEY_LEFT : uint = 37;
		public static const KEY_RIGHT : uint = 39;
		
		public static const DELAY_WALL : uint = 10;
		
		private static const MAX_SEG_LENGTH : uint = 10;
		
		public static const DIRECTION_LEFT : uint = 0;
		public static const DIRECTION_DOWN : uint = 1;
		public static const DIRECTION_RIGHT : uint = 2;
		public static const DIRECTION_UP : uint = 3;
		
		public static const X : uint = 0;
		public static const Y : uint = 1;
			
		private var nw : Boolean;
		private var x : Number;
		private var y : Number;
		private var vehicle : Motorbike;
		private var wall : Wall;
		private var ia:IA2pp;
	
		private var id : int;
		
		private var isHuman : Boolean;
		private var isDead : Boolean;
		private var direction : int;
		
		private var bm : Bitmap;
		
		private var playerWall : Vector.<TriangleMesh3D> = new Vector.<TriangleMesh3D>(); //Pour la 3D
		
		public function Player(_id:Number, _x:Number, _y:Number, _isHuman:Boolean = true, _direction:int = 0) 
		{
			x = _x;
			y = _y;
			isHuman = _isHuman;
			direction = _direction;
			isDead = false;
			id = _id;
			nw = true;
			
			vehicle = new Motorbike();
			
			ia = new IA2pp( this,  _id );
			
			if ( isHuman )
			{
				Main.game.stage.addEventListener(KeyboardEvent.KEY_DOWN, keyDown);
			}
		}
		
		private function keyDown(e : KeyboardEvent) : void
		{			
			if ( ! isDead )
			{
				if( e.keyCode == KEY_LEFT )
				{
					direction++;
					direction = convertDirection(direction);
				}
				else if( e.keyCode == KEY_RIGHT )
				{
					direction--;
					direction = convertDirection(direction);
				}
					
				wall.insertSegment( x, y, x, y );
			}
		}
		
		public function update() : void
		{
			if ( ! isDead )
			{
				
				if ( wall.getLastLength() > MAX_SEG_LENGTH )
				{
					wall.insertSegment( x, y, x, y );
				}
				
				
				var newX : Number = x;
				var newY : Number = y;
				var x0 : Number = 0;
				var y0 : Number = 0;
				var x1 : Number = 0;
				var y1 : Number = 0;
				
				if ( !isHuman )
				{					
					//direction = Main.game.ia.update (direction, id); //Cette fonction insere aussi un segment
					direction = ia.update();
				}
				
				if( direction == DIRECTION_LEFT )
				{
					newX -= vehicle.getSpeed();
					x0 = newX - vehicle.getWidth() / 2;
					x1 = x;
					y0 = y - vehicle.getHeight() / 2;
					y1 = y + vehicle.getHeight() / 2;
				}
				else if( direction == DIRECTION_RIGHT )
				{
					newX += vehicle.getSpeed();
					x0 = x;
					x1 = newX + vehicle.getWidth() / 2;
					y0 = y - vehicle.getHeight() / 2;
					y1 = y + vehicle.getHeight() / 2;
				}
				else if( direction == DIRECTION_DOWN )
				{
					newY += vehicle.getSpeed();
					x0 = x - vehicle.getHeight() / 2;
					x1 = x + vehicle.getHeight() / 2;
					y0 = y;
					y1 = newY + vehicle.getWidth() / 2;
				}
				else if( direction == DIRECTION_UP )
				{
					newY -= vehicle.getSpeed();
					x0 = x - vehicle.getHeight() / 2;
					x1 = x + vehicle.getHeight() / 2;
					y0 = newY - vehicle.getWidth() / 2;
					y1 = y;
				}	
				
				var lastSegment : Segment = wall.getSegment( wall.getSegmentCount() - 1 );
				lastSegment.x1 = newX;
				lastSegment.y1 = newY;
				
				if(Main.game.check_collision(x0, y0, x1, y1, id) )
				{
					// Mort
					Main.game.stage.removeEventListener(KeyboardEvent.KEY_DOWN, keyDown);
					isDead = true;
					trace('Player ' + id + ' is dead.')
					
					// Tempo avant de détruire son mur
					var timer : Timer = new Timer(DELAY_WALL, 1);					
					timer.addEventListener(TimerEvent.TIMER_COMPLETE, destroyWall);
					timer.start();
				}
				else
				{
					// Pas mort
					x = newX;
					y = newY;
				}
			}
			
			
			nw = false;
		}
		
		private function destroyWall( e : Event = null ) : void
		{
			wall.destroyWall();
		}
		
		public function setWall( _wall : Wall ) : void
		{
			wall = _wall;

			wall.insertSegment( x, y, x, y );
		}
		
		public function getWall() : Wall
		{
			return wall;
		}
		
		public function getCoord () : Array
		{
			var coord : Array = new Array ();
			coord [X] = x;
			coord [Y] = y;
			
			return coord;
		}
		
		public function getLife () : Boolean
		{
			return isDead;
		}
		
		public function addPlane( _plane : TriangleMesh3D ) : TriangleMesh3D
		{
			playerWall.push( _plane );
			return _plane;
		}
		
		public function getPlane( i : int ) : TriangleMesh3D
		{
			return playerWall[i];
		}
		
		public function lastPlane() : TriangleMesh3D
		{	
			return playerWall[ playerWall.length - 1 ];
		}
		
		public function changeLast( plane : TriangleMesh3D ) : TriangleMesh3D
		{
			playerWall[ playerWall.length - 1 ] = plane;
			return plane;
		}
		
		public function wallCount() : int
		{
			return playerWall.length;
		}
		
		public function cleanPlanes() : void
		{
			playerWall = new Vector.< TriangleMesh3D >(0);
		}
		
		public function getDir() : int
		{
			return direction;
		}
		
		public function getVehicle() : Vehicle
		{
			return vehicle;
		}
		
		public function getID() : int
		{
			return id;	
		}
		
		static public function convertDirection( dir:int ) :int 
		{
			var newDir:int = dir;
			newDir = (newDir < Player.DIRECTION_LEFT) ? Player.DIRECTION_UP : newDir;
			newDir = (newDir > Player.DIRECTION_UP) ? Player.DIRECTION_LEFT : newDir;
			
			return newDir;
		}
		
		public function isNew() : Boolean
		{
			return nw;
		}
		
		public function getWallLength() : int
		{
			return wall.getLastLength();
		}
	}
}