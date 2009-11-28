
package i12.data
{
	import flash.net.URLRequest;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.errors.IOError;
	import flash.media.Sound;

	public class SoundLoader extends ILoader
	{
		/******************************************************************************************/
		/* PROPERTIES                                                                             */
		/******************************************************************************************/

		private var sound : Sound;
		
		/******************************************************************************************/
		/* CONSTRUCTORS                                                                           */
		/******************************************************************************************/

		public function SoundLoader( _pool : Pool, _resourceName : String, _resourceURL : String, _synchronous : Boolean )
		{
			super( _pool, _resourceName, _resourceURL, _synchronous );
		}
		
		/******************************************************************************************/
		/* METHODS                                                                                */
		/******************************************************************************************/

		override public function load() : void
		{
			super.load();
			
			sound = new Sound();
			
			sound.addEventListener( Event.COMPLETE, onLoadComplete );
			sound.addEventListener( IOErrorEvent.IO_ERROR, onLoadError );
			
			sound.load( new URLRequest( DATA_URL + resourceURL ) );
		}
		
		/******************************************************************************************/
		/* EVENTS                                                                                 */
		/******************************************************************************************/

		override protected function onLoadError( e : IOErrorEvent ) : void
		{
			sound.removeEventListener( Event.COMPLETE, onLoadComplete );
			sound.removeEventListener( IOErrorEvent.IO_ERROR, onLoadError );

			super.onLoadError( e );
		}

		override protected function onLoadComplete( e : Event ) : void
		{
			sound.removeEventListener( Event.COMPLETE, onLoadComplete );
			sound.removeEventListener( IOErrorEvent.IO_ERROR, onLoadError );
			
			pool.setResource( resourceName, sound );
			
			super.onLoadComplete( e );
		}
	}
}
