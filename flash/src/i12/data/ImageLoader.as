
package i12.data
{
	import flash.net.URLRequest;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.display.BlendMode;
	import flash.geom.Matrix;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.errors.IOError;

	public class ImageLoader extends ILoader
	{
		/******************************************************************************************/
		/* PROPERTIES                                                                             */
		/******************************************************************************************/

		private var loader : Loader;
		
		/******************************************************************************************/
		/* CONSTRUCTORS                                                                           */
		/******************************************************************************************/

		public function ImageLoader( _pool : Pool, _resourceName : String, _resourceURL : String, _synchronous : Boolean )
		{
			super( _pool, _resourceName, _resourceURL, _synchronous );
		}
		
		/******************************************************************************************/
		/* METHODS                                                                                */
		/******************************************************************************************/

		override public function load() : void
		{
			super.load();
			
			loader = new Loader();
			
			loader.contentLoaderInfo.addEventListener( Event.COMPLETE, onLoadComplete );
			loader.contentLoaderInfo.addEventListener( IOErrorEvent.IO_ERROR, onLoadError );

			loader.load( new URLRequest( DATA_URL + resourceURL ) );
		}
		
		/******************************************************************************************/
		/* EVENTS                                                                                 */
		/******************************************************************************************/

		override protected function onLoadError( e : IOErrorEvent ) : void
		{
			loader.contentLoaderInfo.removeEventListener( Event.COMPLETE, onLoadComplete );
			loader.contentLoaderInfo.removeEventListener( IOErrorEvent.IO_ERROR, onLoadError );

			super.onLoadError( e );
		}

		override protected function onLoadComplete( e : Event ) : void
		{
			loader.contentLoaderInfo.removeEventListener( Event.COMPLETE, onLoadComplete );
			loader.contentLoaderInfo.removeEventListener( IOErrorEvent.IO_ERROR, onLoadError );

			var mat : Matrix = new Matrix;
			mat.identity();
			
			var bitmapData : BitmapData = new BitmapData( loader.width, loader.height, true, 0x00000000  );
			bitmapData.draw( loader, mat, null, BlendMode.ADD, null, false );
			
			pool.setResource( resourceName, bitmapData );
			
			super.onLoadComplete( e );
		}
	}
}
