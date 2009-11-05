package  
{
	/**
	 * ...
	 * @author ben
	 */
	public class Segment
	{
		private var SegArray:Array(4)
				
		public function Segment( ix1, iy1, ix2, iy2 : Number ) : void
		{
			x1 = ix1;
			y1 = iy1;
			x2 = ix2;
			y2 = iy2;			
		}
		
		public function GetPosition() : Array
		{
			GetSeg = SegArray;
		}
				
		public function CheckSegmentCollision( x1, y1, x2, y2 : Number ) : Boolean
		{
			var X, x, Y, y : Number;
			
			if ( SegArray[0] <= SegArray[2])
			{ X = SegArray[2]; x = SegArray[0] }
			else {  x = SegArray[2]; X = SegArray[0] }
		
			if ( SegArray[1] <= SegArray[3])
			{ Y = SegArray[3]; y = SegArray[1] }
			else {  y = SegArray[3]; Y = SegArray[1] }
			
			
			if (x2 >= x && x1 <= X) && (y2 >= y && y1 <= Y)
			{
				return true;
			}
			
			return false;
			
		}
		

	}

}