package  
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	public class Player
	{
		public const KEY_LEFT : uint = 37;
		public const KEY_RIGHT : uint = 39;
		
		public const DIRECTION_LEFT : int = 0;
		public const DIRECTION_DOWN : int = 1;
		public const DIRECTION_RIGHT : int = 2;
		public const DIRECTION_UP : int = 3;
		
		private var x : Number;
		private var y : Number;
		private var game : Game;
		private var vehicle : Motorbike;
		private var wall : Wall;
	
		private var id : int;
		
		private var isHuman : Boolean;
		private var isDead : Boolean;
		private var direction : int;
		
		private var bm : Bitmap;
		
		public function Player(_game:Game, _x:Number, _y:Number, _isHuman:Boolean = true, _direction:int = 0) 
		{
			x = _x;
			y = _y;
			game = _game;
			isHuman = _isHuman;
			direction = _direction;
			isDead = false;
			
			vehicle = new Motorbike();			
			
			if( isHuman )
				stage.addEventListener(KeyboardEvent.KEY_DOWN, keyDown);
		}
		
		private function keyDown(e : KeyboardEvent) : void
		{
			if( e.keyCode == KEY_LEFT )
				direction--;
			else if( e.keyCode == KEY_RIGHT )
				direction++;
			
			direction = (direction < 0) ? 3 : direction;
			direction = (direction > 3) ? 0 : direction;
		}
		
		public function update() : void
		{
			var newX : Number = x;
			var newY : Number = y;
			var x0, y0, x1, y1 : Number;
			
			if( direction == DIRECTION_LEFT )
			{
				newX += vehicle.getSpeed();
				x0 = x - vehicle.getWidth() / 2;
				x1 = newX + vehicle.getWidth() / 2;
			}
			else if( direction == DIRECTION_RIGHT )
			{
				newX -= vehicle.getSpeed();
				x0 = newX - vehicle.getWidth() / 2;
				x1 = x + vehicle.getWidth() / 2;
			}
			else if( direction == DIRECTION_DOWN )
			{
				newY += vehicle.getSpeed();
				y0 = y - vehicle.getHeight() / 2;
				y1 = newY + vehicle.getHeight() / 2;
			}
			else if( direction == DIRECTION_UP )
			{
				newY -= vehicle.getSpeed();
				y0 = newY + vehicle.getHeight() / 2;
				y1 = y - vehicle.getHeight() / 2;
			}
			
			if( game.check_collision(id, x0, y0, x1, y1) )
			{
				// Mort
				stage.removeEventListener(KeyboardEvent.KEY_DOWN, keyDown);
				isDead = true;
				trace('le player ' + id + 'est mort');
				wall.destroyWall();
			}
			else
			{
				// Pas mort
				x = newX;
				y = newY;
			}
		}
		
		public function setWall( _wall : Wall ) : void
		{
			wall = _wall;
		}
	}

}