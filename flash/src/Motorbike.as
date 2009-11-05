package  
{
	import flash.display.Bitmap;
	import flash.geom.Rectangle;
	/**
	 * Moto ! On utilise une image en attendant le modele 3D
	 * @author thibautp
	 */
	public class Motorbike extends Vehicle
	{
		
		private var image:Bitmap; // A remplacer plus tard par le modele 3D
		
		public function Motorbike() 
		{
			trace("Nouveau Motorbike cree");
			image = new Bitmap(new BitmapData(15, 15, false, 0xFFFF00));
			speed = 1.0;
			height = 15;
			width = 15;
			Main.stage.addChild(image);
		}
		
		/**
		 * Renvoie l'objet graphique representant la moto
		 * @return Un Bitmap colore :)
		 */
		public function getImage() : Bitmap
		{
			trace("Renvoi de image");
			return image;
		}

	}

}