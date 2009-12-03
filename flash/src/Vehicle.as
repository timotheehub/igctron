package  
{
	
	public class Vehicle
	{
		protected var speed:Number = 1;
		protected var width:Number = 10;
		protected var height:Number = 10;
		
		public function Vehicle () 
		{
		}
		
		public function getSpeed() : Number
		{
			//trace("Renvoi de speed");
			return speed;
		}
		
		public function getWidth() : Number
		{
			//trace("Renvoi de width");
			return width;
		}
		
		public function getHeight() : Number
		{
			//trace("Renvoi de height");
			return height;
		}
	}

}