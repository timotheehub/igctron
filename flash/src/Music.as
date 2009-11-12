package  
{
	import flash.events.Event;
	import flash.media.Sound;
	import flash.media.SoundTransform;
	import flash.media.SoundChannel;
	import flash.net.URLRequest;
	
	public class Music
	{
		private var music : Sound;
		private var soundVolume : Number = 1;
		private var soundTransform : SoundTransform;
		private var soundChannel : SoundChannel;
		private var currentMusic : int = 0;
		private var typeMusic : int = 0;
		private var listMusic : Array = [[0],[0]];
		
		public function Music() 
		{
			listMusic[0][0] = new Sound( new URLRequest("music/menu.mp3") );
			listMusic[1][0] = new Sound( new URLRequest("music/game0.mp3") );
			listMusic[1][1] = new Sound( new URLRequest("music/game1.mp3") );
			
			soundChannel = listMusic[typeMusic][currentMusic].play( );
			soundChannel.soundTransform = new SoundTransform( soundVolume );
			soundChannel.addEventListener( Event.SOUND_COMPLETE, changeMusic );
		}
		
		private function changeMusic( e : Event ) : void
		{
			if ( currentMusic >= listMusic[typeMusic].lenght )
			{
				currentMusic = 0;
			}
			else
			{
				currentMusic++;
			}
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
			soundChannel = listMusic[typeMusic][currentMusic].play( );
			soundChannel.soundTransform = new SoundTransform( soundVolume );
		}
	}
}