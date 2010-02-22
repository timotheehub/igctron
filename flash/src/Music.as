package  
{
	import flash.events.Event;
	import flash.media.Sound;
	import flash.media.SoundTransform;
	import flash.media.SoundChannel;
	import flash.net.URLRequest;
	
	public class Music
	{
		private var main : Main;
		private var music : Sound;
		private var soundTransform : SoundTransform;
		private var soundChannel : SoundChannel;
		private var currentMusic : int = 0;
		private var typeMusic : int = 0;
		private var listMusic : Array = [[0],[0]];
		
		public function Music( _main : Main ) 
		{
			main = _main;
			
			listMusic[0][0] = "Menu_Music_0";
			listMusic[1][0] = "Game_Music_0";
			listMusic[1][1] = "Game_Music_1";
			
			soundChannel = (Sound)(main.getResource(listMusic[typeMusic][currentMusic])).play( );
			soundChannel.soundTransform = new SoundTransform( (Main.OPTION_MUSIC_LEVEL/100) );
			soundChannel.addEventListener( Event.SOUND_COMPLETE, changeMusic );
		}
		
		private function changeMusic( e : Event ) : void
		{
			trace('Music ' + currentMusic + ' to');
			if ( currentMusic >= listMusic[typeMusic].length - 1 )
			{
				currentMusic = 0;
			}
			else
			{
				currentMusic++;
			}
			trace('music ' +currentMusic);
			playSong();
		}
		
		public function menuMusic() : void
		{
			typeMusic = 0;
			currentMusic = 0;
			playSong();
		}
		
		public function gameMusic() : void
		{		
			typeMusic = 1;
			currentMusic = 0;
			playSong();
		}
		
		private function playSong() : void
		{
			soundChannel.stop();
			soundChannel = (Sound)(main.getResource(listMusic[typeMusic][currentMusic])).play( );
			soundChannel.soundTransform = new SoundTransform( (Main.OPTION_MUSIC_LEVEL/100) );
			soundChannel.addEventListener( Event.SOUND_COMPLETE, changeMusic );
		}
	}
}