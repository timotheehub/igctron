package  
{
	/**
	 * ...
	 * @author ben
	 */
	public class Segment
	{
		public var x0 : Number;
		public var x1 : Number;
		public var y0 : Number;
		public var y1 : Number;
			
		public function Segment( ix1 : Number, iy1 : Number, ix2 : Number, iy2 : Number ) : void
		{
			x0 = ix1;
			y0 = iy1;
			x1 = ix2;
			y1 = iy2;			
		}
				
		public function checkSegmentCollision( _x1 : Number, _y1 : Number, _x2 : Number, _y2 : Number ) : Boolean
		{
			var X : Number;
			var x : Number;
			var Y : Number;
			var y : Number;
			
			if ( x0 <= x1 )
			{ X = x1; x = x0 }
			else {  x = x1; X = x0 }
		
			if ( y0 <= y1 )
			{ Y = y1; y = y0 }
			else {  y = y1; Y = y0 }
			
			
			if ((_x2 >= x && _x1 <= X) && (_y2 >= y && _y1 <= Y))
			{
				return true;
			}
			
			return false;
			
		}
		

	}

}