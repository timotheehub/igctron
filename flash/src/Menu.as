package  
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.display.Sprite;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	import flash.net.URLRequest;
	import flash.text.Font;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import gs.TweenLite;
	import gs.easing.*;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	
	public class Menu
	{
		private const DUREE_TRANSITION : Number = 1;
		private const KEYBOARD_LEFT : uint = 37;
		private const KEYBOARD_RIGHT : uint = 39;
		private const KEYBOARD_ENTER : uint = 13;
		private const KEYBOARD_SPACE : uint = 32;
		private const MENU_LABEL_Y : int = 300;
		
		private var main : Main;
		private var stage : Stage;
		private var background : Menu_Background;
		private var state : uint;
		private var list : Array;
		private var spots : Array;
		private var rondDesItems : Sprite;
		private var spotItem0 : int;
		
		private const nbItemMenu : Array = new Array( 3, 2 );
		
		private var oldMenuLabel : TextField;
		private var newMenuLabel : TextField;
		
		private var cookie_param : Cookie;
		
		public function Menu( _main : Main, _stage : Stage ) 
		{
			main = _main;
			stage = _stage;
			state = 0;
			list = new Array();
			spots = new Array();
			spotItem0 = 0;
			
			cookie_param = new Cookie( "igc_tron_param" );
			cookie_param.write( "keybord_left", 37 );
			cookie_param.write( "keybord_right", 39 );
			cookie_param.write( "music_level", 50 );
			cookie_param.write( "sound_level", 50 );
			cookie_param.write( "graphic_level", 5 );
			
			background = new Menu_Background( stage.stageWidth, stage.stageHeight );
			stage.addChild(background);
			
			rondDesItems = new Sprite();
			rondDesItems.x = stage.stageWidth / 2;
			rondDesItems.y = stage.stageHeight / 5;
			stage.addChild(rondDesItems);
			
			oldMenuLabel = new TextField();
			oldMenuLabel.autoSize = "left";
			oldMenuLabel.textColor = 0x51FFAE;
			oldMenuLabel.selectable = false;
			oldMenuLabel.embedFonts = true;
			stage.addChild(oldMenuLabel);
			
			newMenuLabel = new TextField();
			newMenuLabel.autoSize = "left";
			newMenuLabel.textColor = 0x51FFAE;
			newMenuLabel.selectable = false;
			newMenuLabel.embedFonts = true;

			var font : Font = new Main.Horseshoes();
			var format : TextFormat = new TextFormat();
			format.font = font.fontName;
			format.bold  = false;
			format.size = 60;

			newMenuLabel.defaultTextFormat = format;
			oldMenuLabel.defaultTextFormat = format;
			
			//newMenuLabel.visible = false;
			stage.addChild(newMenuLabel);
			
			var angleInclinaison : Number = (20 * Math.PI / 180);
			var rayon : Number = 30 * nbItemMenu[state] + 200;
			for (var i : int = 0 ; i < nbItemMenu[state] ; i++)
			{
				// Initialisation des spots
				var spot : Object = new Object();
				var angle : Number = (2 * Math.PI / nbItemMenu[state]) * i;
				spot.x = Math.sin(angle) * rayon;
				spot.scale = ( 3 + Math.cos(angle) ) / 4;
				spot.y = Math.sin(angleInclinaison) * rayon * Math.cos(angle) * spot.scale;
				spots[i] = spot;
				
				// Chargement des images				
				var bmpdata : BitmapData = (BitmapData)(main.getResource( "Menu_Image_0_"+i ));
				var bmp : Bitmap = new Bitmap(bmpdata);
				bmp.x = - bmp.width / 2;
				bmp.y = - bmp.height / 2;
				
				var container : Sprite = new Sprite();
				container.name = "Menu_0_" + i;
				container.x = spot.x;
				container.y = spot.y;
				container.scaleX = spot.scale;
				container.scaleY = spot.scale;
				list[i] = container;
				//container.addEventListener( MouseEvent.CLICK, updateMenu );
				container.addChild(bmp);
				
				rondDesItems.addChild(container);
			}
			triBulle();
			
			newMenuLabel.text = 'Solo';
			newMenuLabel.x = ( stage.stageWidth - newMenuLabel.width ) / 2;
			newMenuLabel.y = MENU_LABEL_Y;
			oldMenuLabel.y = MENU_LABEL_Y;
			
			stage.addEventListener( KeyboardEvent.KEY_DOWN, keyboardEvent );
		}
		
		private function launchMenu( _index : int ) : void
		{
			stage.removeEventListener( KeyboardEvent.KEY_DOWN, keyboardEvent );
			if ( _index == 0 )
			{
				// Lancement du solo
				trace('solo');
				stage.removeChild(oldMenuLabel);
				stage.removeChild(newMenuLabel);
				stage.removeChild(background);
				stage.removeChild(rondDesItems);
				background.stopScintillement = true;
				main.initGame();
			}
			else if ( _index == 1 )
			{
				// Lancement du multi
				trace('multi');
				background.stopScintillement = true;
			}
			else if ( _index == 2 )
			{
				// Affichage des options
				trace('options');
				background.stopScintillement = true;
			}
		}
		
		private function updateMenu( e : Event = null ) : void
		{
			var menuSelected : int = (String)(e.currentTarget.name).substr(7);
			var frontMenu : int = (nbItemMenu[state] - spotItem0) % nbItemMenu[state];
			if ( menuSelected == frontMenu )
			{
				launchMenu(menuSelected);
			}
			else
			{
				stage.removeEventListener( KeyboardEvent.KEY_DOWN, keyboardEvent );
				spotItem0 = (nbItemMenu[state] - menuSelected) % nbItemMenu[state];
				
				// Passage du 0 au premier plan
				for (var i : int = 0 ; i < nbItemMenu[state] ; i++)
				{
					var container : Sprite = list[i];
					var spot : Object = spots[(i + spotItem0) % nbItemMenu[state]];
					
					TweenLite.to(container, DUREE_TRANSITION, { x:spot.x, y:spot.y, scaleX:spot.scale, scaleY:spot.scale, ease:Quad.easeInOut } );
					var timer : Timer = new Timer(DUREE_TRANSITION * 1000, 1);					
					timer.addEventListener(TimerEvent.TIMER_COMPLETE, reenableKeybord);
					timer.start();
				}
			}
			/*stage.removeChild(rondDesItems);
			main.initGame();*/
		}
		
		private function keyboardEvent( e : KeyboardEvent = null ) : void
		{
			if ( e.keyCode == KEYBOARD_LEFT || e.keyCode == KEYBOARD_RIGHT )
			{
				oldMenuLabel.text = newMenuLabel.text;
				oldMenuLabel.x = newMenuLabel.x;
				
				stage.removeEventListener( KeyboardEvent.KEY_DOWN, keyboardEvent );
				if( e.keyCode == KEYBOARD_LEFT )
				{
					spotItem0++;
					newMenuLabel.x = - newMenuLabel.width;
				}
				else
				{
					spotItem0--;
					newMenuLabel.x = stage.stageWidth + newMenuLabel.width;
				}
				if ( spotItem0 < 0 ) 
					spotItem0 = nbItemMenu[state] - 1;
				spotItem0 = spotItem0 % nbItemMenu[state];
				
				switch ((nbItemMenu[state] - spotItem0) % nbItemMenu[state])
				{
					case 0 : newMenuLabel.text = "Solo"; break;
					case 1 : newMenuLabel.text = "Multi"; break;
					case 2 : newMenuLabel.text = "Options"; break;
					default : newMenuLabel.text = "Erreur"; break;
				}
				if ( newMenuLabel.x > 0 )
				{
					TweenLite.to(oldMenuLabel, DUREE_TRANSITION, { x: -oldMenuLabel.width, ease:Quad.easeIn } );
					TweenLite.to(newMenuLabel, DUREE_TRANSITION, { x:((stage.stageWidth-newMenuLabel.width)/2), ease:Quad.easeOut } );
				}
				else
				{
					TweenLite.to(oldMenuLabel, DUREE_TRANSITION, { x: (stage.stageWidth+oldMenuLabel.width), ease:Quad.easeIn } );
					TweenLite.to(newMenuLabel, DUREE_TRANSITION, { x:(stage.stageWidth-newMenuLabel.width)/2, ease:Quad.easeOut } );
				}			
				
				for (var i : int = 0 ; i < nbItemMenu[state] ; i++)
				{
					var container : Sprite = list[i];
					var spot : Object = spots[(i + spotItem0) % nbItemMenu[state]];
					
					TweenLite.to(container, DUREE_TRANSITION, { x:spot.x, y:spot.y, scaleX:spot.scale, scaleY:spot.scale, ease:Quad.easeInOut } );
					var timer : Timer = new Timer(DUREE_TRANSITION * 1000, 1);					
					timer.addEventListener(TimerEvent.TIMER_COMPLETE, reenableKeybord);
					timer.start();
				}
			}
			else if ( e.keyCode == KEYBOARD_ENTER || e.keyCode == KEYBOARD_SPACE )
			{
				launchMenu((nbItemMenu[state] - spotItem0) % nbItemMenu[state]);
			}
		}
		
		private function reenableKeybord( e : Event = null ) : void
		{
			triBulle();
			stage.addEventListener( KeyboardEvent.KEY_DOWN, keyboardEvent );
		}
		
		private function triBulle() : void
		{
			var en_desordre : Boolean = true;
			for ( var i : int = 0 ; (i < nbItemMenu[state]-1) && en_desordre ; ++i )
			{
				en_desordre = false;
				for ( var j : int = 0 ; j < nbItemMenu[state] - 1 - i ; ++j )
				{
					if ( rondDesItems.getChildAt(j).y < rondDesItems.getChildAt(j+1).y )
					{
						rondDesItems.setChildIndex(rondDesItems.getChildAt(j+1), j);
						en_desordre = true;
					}
				}
			}
		}
	}
}