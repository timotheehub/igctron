package  
{
	/**
	 * Vehicule generique
	 * @author thibautp
	 */
	public class Vehicle
	{
		private var speed:Number;
		
		public function Vehicle() 
		{
			trace("Nouveau Vehicle cree");
		}
		
		/**
		 * Renvoie la vitesse du vehicle
		 */
		public function get speed() : Number
		{
			return speed;
		}
	}

}