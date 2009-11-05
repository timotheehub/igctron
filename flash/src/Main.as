package 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	
	public class Main extends Sprite 
	{
		private var background : Bitmap;
		
		private var objects : Shape;
		
		private var game : Game;
		
		public function Main() : void 
		{
			if ( stage != null )
				init();
			else
				addEventListener( Event.ADDED_TO_STAGE, init );
		}
		
		private function init( e : Event = null ) : void 
		{
			removeEventListener( Event.ADDED_TO_STAGE, init );
			
			addChild( background = new Bitmap( new BitmapData( stage.stageWidth, stage.stageHeight, false, 0x00 ) ) );
			
			addChild( objects = new Shape() );
			
			game = new Game();
			
			game.addPlayer( new Player( game, 300, 400, true, Player.DIRECTION_UP ) );
			game.addPlayer( new Player( game, 400, 400, false, Player.DIRECTION_UP ) );
			game.addPlayer( new Player( game, 500, 400, false, Player.DIRECTION_UP ) );
			game.addPlayer( new Player( game, 600, 400, false, Player.DIRECTION_UP ) );
			
			stage.addEventListener( Event.ENTER_FRAME, loop );
		}
		
		private function loop( e : Event = null ) : void
		{
			game.update();
			
			objects.graphics.clear();
			
			for ( var k : int = 0 ; k < game.getPlayerCount() ; k++ )
			{
				var player : Player = game.getPlayer(k);
				
				objects.graphics.drawCircle( player.x, player.y, 6 );
			}
			
			for ( var p : int = 0 ; p < game.getWallCount() ; p++ )
			{
				var wall : Wall = game.getWall(p);
				
				objects.graphics.drawCircle( player.x, player.y, 6 );
				
				for ( var q : int = 0 ; q < wall.getSegmentCount() ; q++ )
				{
					var segment : Segment = wall.getSegment(q);
					
					objects.graphics.moveTo( segment.x0, segment.y0 );
					objects.graphics.lineTo( segment.x1, segment.y1 );
				}
			}
			
			
		}
		
	}
	
}