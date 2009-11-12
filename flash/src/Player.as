package  
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	public class Player
	{
		public static const KEY_LEFT : uint = 37;
		public static const KEY_RIGHT : uint = 39;
		
		public static const DIRECTION_LEFT : int = 0;
		public static const DIRECTION_DOWN : int = 1;
		public static const DIRECTION_RIGHT : int = 2;
		public static const DIRECTION_UP : int = 3;
		
		public var x : Number;
		public var y : Number;
		private var game : Game;
		private var vehicle : Motorbike;
		private var wall : Wall;
	
		private var id : int;
		
		private var isHuman : Boolean;
		public var isDead : Boolean;
		private var direction : int;
		
		private var bm : Bitmap;
		
		public function Player(_game:Game, _id:Number, _x:Number, _y:Number, _isHuman:Boolean = true, _direction:int = 0) 
		{
			x = _x;
			y = _y;
			game = _game;
			isHuman = _isHuman;
			direction = _direction;
			isDead = false;
			id = _id;
			
			vehicle = new Motorbike();			
			
			if ( isHuman )
			{
				game.stage.addEventListener(KeyboardEvent.KEY_DOWN, keyDown);
			}
			else
			{
				
			}
		}
		
		private function keyDown(e : KeyboardEvent) : void
		{			
			if ( ! isDead )
			{
				if( e.keyCode == KEY_LEFT )
					direction++;
				else if( e.keyCode == KEY_RIGHT )
					direction--;
				
				direction = (direction < DIRECTION_LEFT) ? DIRECTION_UP : direction;
				direction = (direction > DIRECTION_UP) ? DIRECTION_LEFT : direction;
				
				wall.insertSegment( x, y, x, y );
			}
		}
		
		public function update() : void
		{
			if ( ! isDead )
			{
				var newX : Number = x;
				var newY : Number = y;
				var x0 : Number = 0;
				var y0 : Number = 0;
				var x1 : Number = 0;
				var y1 : Number = 0;
				
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
				
				//trace ( "joueur : " + x0 + " ; " + y0 + " ; " + x1 + " ; " + y1);
				if( game.check_collision(x0, y0, x1, y1, id) )
				{
					// Mort
					game.stage.removeEventListener(KeyboardEvent.KEY_DOWN, keyDown);
					isDead = true;
					trace('le player ' + id + ' est mort');
					wall.destroyWall();
				}
				else
				{
					// Pas mort
					x = newX;
					y = newY;
				}
			}
		}
		
		public function setWall( _wall : Wall ) : void
		{
			wall = _wall;

			wall.insertSegment( x, y, x, y );
		}
	}
}