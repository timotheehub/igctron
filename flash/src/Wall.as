package  
{
	
	/**
	 * ...
	 * @author ben
	 */
	public class Wall
	{
		private var WallArray:Vector.<Segment> = new Vector.<Segment>();
		
		private const MIN_X : Number = 0;
		private const MIN_Y : Number = 0;
		private const MAX_X : Number = Main.PLANE_WIDTH;
		private const MAX_Y : Number = Main.PLANE_HEIGHT;
		
		
		public function Wall( MyPlayer : Player) 
		{
			MyPlayer.setWall(this);
		}
		
		public function insertSegment( x1 : Number, y1 : Number, x2 : Number, y2 : Number ) : void // format d'entrée ?
		{
			var Seg:Segment = new Segment(x1, y1, x2, y2);
			
			WallArray.push( Seg );
		}
		
		public function checkWallCollision ( x1 : Number, y1 : Number, x2 : Number, y2 : Number, idPlayer : Number, idWall : Number ) : Boolean
		{
			var lastSegment:int = WallArray.length;
			
			if ( idPlayer == idWall )
			{
				lastSegment -= 2; // no collision avalaible
			}
			
			if (x1 <= MIN_X || x2 >= MAX_X || y1 <= MIN_Y || y2 >= MAX_Y)
			{
				return true;
			}
			
			for (var i : int = 0; i < lastSegment; i++)
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
			WallArray = new Vector.<Segment>(0); // better solution ?
		}
		
		public function getLastLength() : int
		{
			return WallArray[ WallArray.length -1].length();
		}
	}

}