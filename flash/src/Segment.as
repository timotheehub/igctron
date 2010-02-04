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
				
		public function checkSegmentCollision( _x0 : Number, _y0 : Number, _x1 : Number, _y1 : Number ) : Boolean
		{
			var X : Number;
			var x : Number;
			var Y : Number;
			var y : Number;
			
			if ( x0 <= x1 )
			{
				X = x1;
				x = x0;
			}
			else
			{  
				x = x1;
				X = x0; 
			}
		
			if ( y0 <= y1 )
			{ 
				Y = y1; 
				y = y0;
			}
			else 
			{  
				y = y1;
				Y = y0;
			}
			
			if ((_x1 > x && _x0 < X) && (_y1 > y && _y0 < Y))
			{
				return true;
			}
			
			return false;
			
		}
		
		public function getXmin() : Number
		{
			if ( x0 <= x1 )
			{
				return x0;
			}
			return x1;
		}
		
		public function getXmax() : Number
		{
			if ( x0 >= x1 )
			{
				return x0;
			}
			return x1;
		}
		
		public function getYmin() : Number
		{
			if ( y0 <= y1 )
			{ 
				return y0;
			}
			return y1;
		}
		
		public function getYmax() : Number
		{
			if ( y0 >= y1 )
			{ 
				return y0;
			}
			return y1;
		}
		
		public function length() : int
		{
			if ( x0 == x1 )
			{
				return Math.abs(y1 - y0);
			}
			
			return Math.abs(x1 - x0);
		}

	}

}