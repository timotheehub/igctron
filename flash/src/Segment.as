package  
{
	/**
	 * ...
	 * @author ben
	 */
	public class Segment
	{
		private var SegArray:Array
				
		public function Segment( ix1 : Number, iy1 : Number, ix2 : Number, iy2 : Number ) : void
		{
			SegArray[0] = ix1;
			SegArray[1] = iy1;
			SegArray[2] = ix2;
			SegArray[3] = iy2;			
		}
		
		public function GetPosition() : Array
		{
			return SegArray;
		}
				
		public function CheckSegmentCollision( x1 : Number, y1 : Number, x2 : Number, y2 : Number ) : Boolean
		{
			var X : Number;
			var x : Number;
			var Y : Number;
			var y : Number;
			
			if ( SegArray[0] <= SegArray[2])
			{ X = SegArray[2]; x = SegArray[0] }
			else {  x = SegArray[2]; X = SegArray[0] }
		
			if ( SegArray[1] <= SegArray[3])
			{ Y = SegArray[3]; y = SegArray[1] }
			else {  y = SegArray[3]; Y = SegArray[1] }
			
			
			if ((x2 >= x && x1 <= X) && (y2 >= y && y1 <= Y))
			{
				return true;
			}
			
			return false;
			
		}
		

	}

}