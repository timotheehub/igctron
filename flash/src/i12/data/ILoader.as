
package i12.data
{
	import flash.events.Event;
	import flash.events.IOErrorEvent;

	public class ILoader
	{
		/******************************************************************************************/
		/* CONSTANTES                                                                             */
		/******************************************************************************************/

		//protected static var DATA_URL : String = "file://C:/.../bin/";
		//protected static var DATA_URL : String = "http://impulse12.com/.../bin/";
		protected static var DATA_URL : String = "";

		/******************************************************************************************/
		/* PROPERTIES                                                                             */
		/******************************************************************************************/

		protected var pool : Pool;
		
		protected var resourceName : String;
		protected var resourceURL : String;
		
		protected var synchronous : Boolean;
		
		/******************************************************************************************/
		/* CONSTRUCTORS                                                                           */
		/******************************************************************************************/

		public function ILoader( _pool : Pool, _resourceName : String, _resourceURL : String, _synchronous : Boolean )
		{
			pool = _pool;
			
			resourceName = _resourceName;
			resourceURL = _resourceURL;
			
			synchronous = _synchronous;
			
			if ( pool.getLoader( resourceURL ) != null )
			{
				trace( "Warning : Resource " + resourceURL + " already loaded." );
				
				return;
			}
			
			pool.setLoader( resourceURL, this );
			
			if ( synchronous )
				pool.pushLoader( this );
			else
				load();
		}
		
		/******************************************************************************************/
		/* ACCESSORS                                                                              */
		/******************************************************************************************/

		public function getPercent() : Number
		{
			return 0.0;
		}

		/******************************************************************************************/
		/* METHODS                                                                                */
		/******************************************************************************************/

		public function load() : void
		{
			if ( synchronous )
				pool.lock();
		}
		
		/******************************************************************************************/
		/* EVENTS                                                                                 */
		/******************************************************************************************/

		protected function onLoadError( e : IOErrorEvent ) : void
		{
			trace( "Error : Resource " + resourceURL + " not found." ); 

			if ( synchronous )
				pool.unlock();
		}

		protected function onLoadComplete( e : Event ) : void
		{
			trace( "Info : Resource " + resourceURL + " loaded." ); 

			if ( synchronous )
				pool.unlock();
		}
	}
}
