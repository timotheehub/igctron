
package i12.data
{
	import flash.display.Stage;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	
	public class Pool extends EventDispatcher
	{
		/******************************************************************************************/
		/* PROPERTIES                                                                             */
		/******************************************************************************************/

		private var stage : Stage;
		
		private var resources : Array;

		private var loaders : Array;
		
		private var count : int;
		private var index : int;
		
		private var locked : Boolean;
		
		private var running : Boolean;

		/******************************************************************************************/
		/* CONSTRUCTORS                                                                           */
		/******************************************************************************************/

		public function Pool( _stage : Stage ) : void
		{
			stage = _stage;
			
			resources = new Array();
			
			loaders = new Array();
			
			count = 0;
			index = 0;
			
			locked = false;
		}

		/******************************************************************************************/
		/* ACCESSORS                                                                              */
		/******************************************************************************************/

		public function getResource( _name : String ) : Object
		{
			if ( resources.hasOwnProperty( _name ) )
				return resources[_name];
			
			trace( "Warning : Resource " + _name + " not loaded." );
				
			return null;
		}
		
		public function setResource( _name : String, _resource : Object ) : void
		{
			resources[_name] = _resource;
		}

		public function getLoader( _url : String ) : ILoader
		{
			return loaders[_url];
		}
		
		public function setLoader( _url : String, _loader : ILoader ) : void
		{
			loaders[_url] = _loader;
		}

		public function getPercent() : Number
		{
			if ( running )
			{
				return index / count;
			}
			else
			{
				return 1.0;
			}
		}
		
		public function isRunning() : Boolean
		{
			return running;
		}

		/******************************************************************************************/
		/* METHODS                                                                                */
		/******************************************************************************************/

		public function lock() : void
		{
			locked = true;
		}

		public function unlock() : void
		{
			locked = false;
		}

		public function pushLoader( _loader : ILoader ) : void
		{
			loaders[index++] = _loader;
		}
		
		public function popLoader() : ILoader
		{
			return loaders[--index];
		}

		public function beginLoading() : void
		{
			running = true;
			
			count = index;
			index = 0;
			
			locked = false;

			stage.addEventListener( Event.ENTER_FRAME, onLoop );
		}
		
		public function endLoading() : void
		{
			running = false;
			
			count = 0;
			index = 0;
			
			locked = false;
			
			stage.removeEventListener( Event.ENTER_FRAME, onLoop );
			
			dispatchEvent( new Event( Event.COMPLETE ) );
		}
		
		/******************************************************************************************/
		/* EVENTS                                                                                 */
		/******************************************************************************************/

		private function onLoop( e : Event ) : void
		{
			if ( locked ) return;
			
			if ( index < count )
				loaders[index++].load();
			else
				endLoading();
		}
	}
}