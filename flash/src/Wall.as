package  
{
	
	import Segment;
	
	/**
	 * ...
	 * @author ben
	 */
	public class Wall
	{
		var WallArray:Array;
		private var taille:int = 0;
		
		public function Wall( MyPlayer : Player) 
		{
			MyPlayer.setWall(this);
		}
		
		public function InsertSegment( x1, y1, x2, y2 : Number ) : void // format d'entrée ?
		{
			var Seg:Segment = new Segment(x1, y1, x2, y2);
			
			WallArray[taille] = Seg;
			taille++;
		}
		
		public function CheckWallCollision ( x1, y1, x2, y2 : Number ) : Boolean
		{
			for (i = 0; i <= taille; i++)
			{
				if (CheckSegmentCollision(x1, y1, x2, y2) == true)
				{
					return true;
				}
			}
			
			return false;
		}
		
		public function GetSegmentCount() : int
		{
			return taille;
		}
		
		public function GetSegment( position : int ) : Segment
		{
			return WallArray[position];
		}
		
		public function destroyWall();
		{
			for ( i=; i<=taille; i++)
			{
				WallArray[i - 1] = null;
			}
		}
		
	}

}