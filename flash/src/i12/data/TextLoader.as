
package i12.data
{
	import flash.net.URLRequest;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.errors.IOError;
	import flash.net.URLStream;

	public class TextLoader extends ILoader
	{
		/******************************************************************************************/
		/* PROPERTIES                                                                             */
		/******************************************************************************************/

		private var stream : URLStream;
		
		/******************************************************************************************/
		/* CONSTRUCTORS                                                                           */
		/******************************************************************************************/

		public function TextLoader( _pool : Pool, _resourceName : String, _resourceURL : String, _synchronous : Boolean )
		{
			super( _pool, _resourceName, _resourceURL, _synchronous );
		}
		
		/******************************************************************************************/
		/* METHODS                                                                                */
		/******************************************************************************************/

		override public function load() : void
		{
			super.load();
			
			stream = new URLStream();
			
			stream.addEventListener( Event.COMPLETE, onLoadComplete );
			stream.addEventListener( IOErrorEvent.IO_ERROR, onLoadError );
			
			stream.load( new URLRequest( Flouzer.DATA_URL + resourceURL ) );
		}
		
		/******************************************************************************************/
		/* EVENTS                                                                                 */
		/******************************************************************************************/

		override protected function onLoadError( e : IOErrorEvent ) : void
		{
			stream.removeEventListener( Event.COMPLETE, onLoadComplete );
			stream.removeEventListener( IOErrorEvent.IO_ERROR, onLoadError );

			super.onLoadError( e );
		}

		override protected function onLoadComplete( e : Event ) : void
		{
			stream.removeEventListener( Event.COMPLETE, onLoadComplete );
			stream.removeEventListener( IOErrorEvent.IO_ERROR, onLoadError );
			
			pool.setResource( resourceName, new String( stream.readMultiByte( stream.bytesAvailable, "iso-8859-1" ) ) );
			
			super.onLoadComplete( e );
		}
	}
}
