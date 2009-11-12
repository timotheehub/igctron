package  
{
	public class IA
	{
		private var numero :int = 0;
		
		public function IA() 
		{
			numero = (int)(Math.random()*2) + 1;
		}
		
		public function update(direction : int, wall : Wall) : int {
			var newdirection;
			
			if (numero == 1) 
			{
				newdirection = IA1.update(direction);
			} 
			else if (numero == 2) 
			{
				newdirection = IA2.update2(direction);
			}
			
			if (newdirection != direction)
			{
				wall.insertSegment( x, y, x, y );
			}
			
			return newdirection;
		}
		
	}

}