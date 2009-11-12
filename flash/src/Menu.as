package  
{
	import flash.display.Loader;
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.net.URLRequest;
	
	public class Menu
	{
		private var main : Main;
		private var stage : Stage;
		private var state : uint;
		private var list : Array;
		private var selectedItem : uint;
		
		private const nbItemMenu : Array = new Array( 3, 2 );
		
		public function Menu( _main : Main, _stage : Stage ) 
		{
			main = _main;
			stage = _stage;
			state = 0;
			selectedItem = 0;
			list = new Array();
			
			
			// initialiser la liste
			for (var i : int = 0 ; i < nbItemMenu[state] ; i++)
			{
				var loaderImage : Loader = new Loader();
				
				loaderImage.load(new URLRequest("img/menu_0_" + i + ".jpg"));
				loaderImage.x = (selectedItem==i)?100:50;
				loaderImage.y = 100 * i + 50;
				if ( i == 0 )
					loaderImage.addEventListener( MouseEvent.CLICK, launchSolo );
				stage.addChild(loaderImage);
				
				list[i] = loaderImage;
			}
		}
		
		private function launchSolo( e : Event = null ) : void
		{
			for (var i : int = 0 ; i < nbItemMenu[state] ; i++)
			{
				stage.removeChild(list[i]);
			}
			main.initGame();
		}
	}
}