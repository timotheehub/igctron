package  
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.filters.BlurFilter;
	import flash.filters.GlowFilter;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import flash.events.Event;
	
	public class Menu_Background extends Sprite
	{
		private const NB_CARRES_LARGEUR : int = 27;
		private const NB_CARRES_PROFONDEUR : int = 10;
		private const LARGEUR_CARRE : int = 50;
		private const PROFONDEUR : int = 700;
		private const Y_DEPART : int = 300;
		private const DUREE_MAX_RANDOM_TIMER : int = 100;
		
		private var widthMax : int;
		private var heightMax : int;
		private var stars : Sprite;
		public var stopScintillement : Boolean = false;
		
		public function Menu_Background( _width : int, _height : int ) 
		{
			widthMax = _width;
			heightMax = _height;
			var i : int;
			var bmpData : BitmapData = new BitmapData( 1, 1, false, 0xFFFFFF );
			stars = new Sprite();
			addChild(stars);
			for ( i = 0 ; i < 1000 ; i++ )
			{
				var bmp : Bitmap = new Bitmap(bmpData);
				bmp.x = (int)(Math.random() * widthMax);
				bmp.y = (int)(Math.random() * heightMax);
				stars.addChild(bmp);
			}
			var timer : Timer = new Timer(Math.random() * DUREE_MAX_RANDOM_TIMER, 1);					
			timer.addEventListener(TimerEvent.TIMER_COMPLETE, scintillement);
			timer.start();
			
			var shape : Shape = new Shape();
			shape.graphics.beginFill(0x000000);
			shape.graphics.lineStyle(1, 0x00FF00, 0.5);
			
			var y_precedent : Number = Y_DEPART;
			for ( i = 0 ; i <= NB_CARRES_PROFONDEUR ; i++ )
			{
				// Lignes horizontales
				shape.graphics.moveTo(widthMax/2 - (( PROFONDEUR - Y_DEPART + y_precedent ) * LARGEUR_CARRE * NB_CARRES_LARGEUR / 2) / PROFONDEUR, y_precedent);
				shape.graphics.lineTo(widthMax/2 + (( PROFONDEUR - Y_DEPART + y_precedent ) * LARGEUR_CARRE * NB_CARRES_LARGEUR / 2) / PROFONDEUR, y_precedent);
				if ( i != NB_CARRES_PROFONDEUR )
				{
					y_precedent = y_precedent - LARGEUR_CARRE * ((1.2 * NB_CARRES_PROFONDEUR - i) / (1.2 * NB_CARRES_PROFONDEUR));
				}
			}
			for ( i = 0 ; i <= NB_CARRES_LARGEUR ; i++ )
			{
				// Lignes verticales
				if ( i >= NB_CARRES_LARGEUR / 2 )
				{
					shape.graphics.moveTo(widthMax/2 + (( PROFONDEUR - Y_DEPART + y_precedent ) * LARGEUR_CARRE * (i-NB_CARRES_LARGEUR/2)) / PROFONDEUR, y_precedent);
					shape.graphics.lineTo(widthMax / 2 + (( PROFONDEUR - Y_DEPART + Y_DEPART ) * LARGEUR_CARRE * (i-NB_CARRES_LARGEUR/2)) / PROFONDEUR, Y_DEPART);
				}
				else
				{
					shape.graphics.moveTo(widthMax/2 - (( PROFONDEUR - Y_DEPART + y_precedent ) * LARGEUR_CARRE * (i+.5)) / PROFONDEUR, y_precedent);
					shape.graphics.lineTo(widthMax / 2 - (( PROFONDEUR - Y_DEPART + Y_DEPART ) * LARGEUR_CARRE * (i+.5)) / PROFONDEUR, Y_DEPART);
				}
			}
			shape.graphics.endFill();
			//addChild(shape);
		}
		
		private function scintillement( e : Event = null ) : void
		{
			var i : Number;
			var random : Number = Math.round(Math.random() * 50 + 1);
			var bmpData : BitmapData = new BitmapData( 1, 1, false, 0xFFFFFF );
			for ( i = 0 ; i < random ; i++ )
			{
				stars.removeChildAt( (int)(Math.random() * stars.numChildren) );
				
				var bmp : Bitmap = new Bitmap(bmpData);
				bmp.x = (int)(Math.random() * widthMax);
				bmp.y = (int)(Math.random() * heightMax);
				stars.addChild(bmp);
			}
			
			if( stopScintillement == false )
			{
				var timer : Timer = new Timer(Math.random() * DUREE_MAX_RANDOM_TIMER, 1);		
				timer.addEventListener(TimerEvent.TIMER_COMPLETE, scintillement);
				timer.start();			
			}
		}
		
		public function stop():void
		{
			stopScintillement = true;
		}
	}
}