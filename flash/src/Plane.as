package  
{
	/**
	 * ...
	 * @author Goost
	 */
	public class Plane
	{
		private var width : int;
		private var heigh : int;
		
		public function Plane() 
		{
			
		}
		
		public function setPlane (width : int = 800, heigh : int = 600)
		{
			width = width;
			heigh = heigh;
		}
		
		public function getWidth () : int
		{
			return width;
		}
		
		public function getHeigh () : int
		{
			return heigh;
		}
	}
}