package  
{
	import flash.net.SharedObject;
	
	public class Cookie
	{
		private var so : SharedObject;
		
		public function Cookie ( _name : String )
		{
			so = SharedObject.getLocal(_name);
		}
		
		public function read ( _param_name : String ) : String
		{
			if (so.data[_param_name])
			{
				return so.data[_param_name];
			}
			else
			{
				return "";	
			}
		}

		public function write ( _param_name : String, _param_value : * ) : void
		{
			so.data[_param_name] = _param_value.toString();
			so.flush();
		}
		
		public function destroy ( ) : void
		{
			so.clear();
		}
	}
}