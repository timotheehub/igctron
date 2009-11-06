package  
{
	
	import Segment;
	
	/**
	 * ...
	 * @author ben
	 */
	public class Wall
	{
		private var WallArray:Array = new Array();
		
		public function Wall( MyPlayer : Player) 
		{
			MyPlayer.setWall(this);
		}
		
		public function insertSegment( x1 : Number, y1 : Number, x2 : Number, y2 : Number ) : void // format d'entrée ?
		{
			var Seg:Segment = new Segment(x1, y1, x2, y2);
			
			WallArray.push( Seg );
		}
		
		public function checkWallCollision ( x1 : Number, y1 : Number, x2 : Number, y2 : Number ) : Boolean
		{
			for (var i : int = 0; i < WallArray.length; i++)
			{
				if (WallArray[i].checkSegmentCollision(x1, y1, x2, y2) == true)
				{
					return true;
				}
			}
			
			return false;
		}
		
		public function getSegmentCount() : int
		{
			return WallArray.length;
		}
		
		public function getSegment( position : int ) : Segment
		{
			return WallArray[position];
		}
		
		public function destroyWall() : void
		{
			WallArray = new Array();
		}
		
	}

}