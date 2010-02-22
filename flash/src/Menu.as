package  
{
	import org.papervision3d.core.animation.clip.AnimationClip3D;
	import org.papervision3d.core.proto.SceneObject3D;
	import org.papervision3d.materials.BitmapMaterial;
	import org.papervision3d.materials.utils.MaterialsList;
	import org.papervision3d.objects.DisplayObject3D;
	import org.papervision3d.objects.primitives.Plane;
	import org.papervision3d.view.*;
	import org.papervision3d.cameras.Camera3D;
	import org.papervision3d.render.BasicRenderEngine;
	import org.papervision3d.scenes.Scene3D;
	
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Sprite;
	import flash.display.Stage;
	
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.TimerEvent;
	
	import flash.text.Font;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	import flash.utils.Timer;

	import gs.TweenLite;
	import gs.easing.*;
	
	public class Menu extends Sprite
	{
		private const SCREEN_WIDTH		: int = 800;
		private const SCREEN_HEIGHT		: int = 600;
		
		private const DUREE_TRANSITION 	: Number = 1;
		
		private const KEYBOARD_LEFT 	: uint = 37;
		private const KEYBOARD_RIGHT 	: uint = 39;
		private const KEYBOARD_ENTER 	: uint = 13;
		private const KEYBOARD_SPACE 	: uint = 32;
		
		private const POSITION_ITEMS_Y	: int = 250;
		private const MENU_LABEL_X 		: int = 1000;
		private const MENU_LABEL_Y 		: int = 0;
		private const MENU_LABEL_Z 		: int = -350;
	
		private var camera 				: Camera3D;
		private var viewport 			: Viewport3D;
		private var scene 				: SceneObject3D;
		private var renderer 			: BasicRenderEngine;
		
		private var main 			: Main;
		private var mainStage 		: Stage;
		private var background 		: Menu_Background;
		private var state 			: uint = 0;
		private var items_list		: Array = new Array(new Array("Solo", "Multi", "Options"), new Array("Keys", "Display", "Sound"));
		private var images_list 	: Array = new Array(); // liste des objets Plane contenant les images des menus
		private var spots_list		: Array = new Array(); // liste des positions des items
		private var texts_list		: Array = new Array(); // liste des objets Plane contenant les labels des menus
		private var spotItem0 		: int = 0; // position del'item d'index 0
		
		private var cookie_param 	: Cookie;
		
		public function Menu(_main : Main, _stage : Stage) 
		{
			// Initialisation des paramètres
			main = _main;
			mainStage = _stage;
			
			//loadCookie();
			
			initPapervision();
			
			initMenuItem();
			
			background = new Menu_Background(mainStage.stageWidth, mainStage.stageHeight);
			addChildAt(background, 0);
			
			addEventListener(Event.ENTER_FRAME, render);
			mainStage.addEventListener(KeyboardEvent.KEY_DOWN, keyboardEvent);
		}
		
		public function initPapervision() : void
		{
			viewport = new Viewport3D(0, 0, true);
			addChild(viewport);

			scene = new SceneObject3D();

			camera = new Camera3D();
			scene.addChild(camera);
			camera.z = -700;

			renderer = new BasicRenderEngine();
		}
		
		private function initMenuItem() : void
		{
			var angleInclinaison : Number = (25 * Math.PI)/180;
			var rayon : Number = 400;
			
			// Chargement et ajout des élements du menu (images et textes)
			for (var i : int = 0 ; i < items_list[state].length ; i++)
			{
				// Création d'un objet plane qui va contenir l'image
				var material : BitmapMaterial = new BitmapMaterial((BitmapData)(main.getResource( "Menu_Image_"+state+"_" + i )));
				var plane : Plane = new Plane(material);
				
				// Calcul et sauvegarde de la position de l'objet
				var angle : Number = (i * (360 / items_list[state].length) * Math.PI)/180;
				var spot : Object = new Object();
				spot.x =   rayon * Math.sin(angle);
				spot.y = - rayon * Math.cos(angle) * Math.sin(angleInclinaison) + POSITION_ITEMS_Y;
				spot.z = - rayon * Math.cos(angle) * Math.cos(angleInclinaison);
				spots_list[i] = spot;
				
				// Positionnement et ajout du plan
				plane.x = spot.x;
				plane.y = spot.y;
				plane.z = spot.z;
				images_list[i] = plane;
				
				scene.addChild(plane);
			}
			
			initText();
		}
		
		private function initText() : void
		{
			var font : Font = new Main.Horseshoes();
			var format : TextFormat = new TextFormat();
			format.font = font.fontName;
			format.bold  = false;
			format.size = 60;
			
			for (var i:int = 0; i < items_list[state].length ; i++)
			{
				var tf : TextField = new TextField();
				tf.autoSize = "left";
				tf.textColor = 0x51FFAE;
				tf.selectable = false;
				tf.embedFonts = true;
				tf.defaultTextFormat = format;
				tf.text = items_list[state][i];
				
				var bmpData : BitmapData = new BitmapData(tf.width, tf.height, true, 0x000000);
				bmpData.draw(tf);
				
				var material : BitmapMaterial = new BitmapMaterial(bmpData);
				material.smooth = true;
				material.doubleSided = true;
				
				var plane : Plane = new Plane(material, tf.width, tf.height);
				plane.name = "plane_text_" + i;
				plane.x = MENU_LABEL_X;
				plane.y = MENU_LABEL_Y;
				plane.z = MENU_LABEL_Z;
				texts_list[i] = plane;
				scene.addChild(plane);
			}
			
			// Affichage du premier label
			scene.getChildByName("plane_text_0").x = 0;
		}
		
		private function render(e : Event = null) : void
		{
			renderer.renderScene(scene, camera, viewport);
		}
		
		private function keyboardEvent(e : KeyboardEvent = null) : void
		{
			if(e.keyCode == KEYBOARD_LEFT || e.keyCode == KEYBOARD_RIGHT)
			{
				mainStage.removeEventListener(KeyboardEvent.KEY_DOWN, keyboardEvent);
				
				// Récupération du plan correspondant au label actuel
				var old_behind : int = (items_list[state].length - spotItem0) % items_list[state].length;
				var old_menu_label : Plane = (Plane)(scene.getChildByName("plane_text_"+old_behind));
				
				// Détermination de la nouvelle organisation
				if(e.keyCode == KEYBOARD_LEFT)
					spotItem0 = (++spotItem0 >= items_list[state].length) ? spotItem0 = 0 : spotItem0 = spotItem0;
				else
					spotItem0 = (--spotItem0 < 0) ? spotItem0 = items_list[state].length - 1 : spotItem0 = spotItem0;
				
				// Récupération du plan correspondant au nouveau label
				var new_behind : int = (items_list[state].length - spotItem0) % items_list[state].length;
				var new_menu_label : Plane = (Plane)(scene.getChildByName("plane_text_"+new_behind));
				
				// Déplacement des labels
				if (e.keyCode == KEYBOARD_LEFT)
				{
					new_menu_label.x = -MENU_LABEL_X;
					TweenLite.to(old_menu_label, DUREE_TRANSITION, {x:MENU_LABEL_X, ease:Quad.easeIn} );
					TweenLite.to(new_menu_label, DUREE_TRANSITION, {x:0, ease:Quad.easeOut} );
				}
				else
				{
					new_menu_label.x = MENU_LABEL_X;
					TweenLite.to(old_menu_label, DUREE_TRANSITION, {x:-MENU_LABEL_X, ease:Quad.easeIn} );
					TweenLite.to(new_menu_label, DUREE_TRANSITION, {x:0, ease:Quad.easeOut} );
				}
				
				// Modification des positions des images
				for(var i : int = 0 ; i < items_list[state].length ; i++)
				{
					var plane : Plane = images_list[i];
					var spot : Object = spots_list[(i + spotItem0) % items_list[state].length];
					
					TweenLite.to(plane, DUREE_TRANSITION, {x:spot.x, y:spot.y, z:spot.z, ease:Quad.easeInOut} );
					var timer : Timer = new Timer(DUREE_TRANSITION * 1000, 1);					
					timer.addEventListener(TimerEvent.TIMER_COMPLETE, reenableKeybord);
					timer.start();
				}
			}
			else if(e.keyCode == KEYBOARD_ENTER || e.keyCode == KEYBOARD_SPACE)
			{
				// Sélection d'un objet du menu
				launchItem((items_list[state].length - spotItem0) % items_list[state].length);
			}
		}
		
		private function reenableKeybord(e : Event = null) : void
		{
			mainStage.addEventListener(KeyboardEvent.KEY_DOWN, keyboardEvent);
		}
		
		private function launchItem(_index : int) : void
		{
			mainStage.removeEventListener(KeyboardEvent.KEY_DOWN, keyboardEvent);
			
			if (state == 0 && _index == 0)
			{
				// Solo
				trace('solo');
				
				scene = null;
				removeEventListener(Event.ENTER_FRAME, render);
				background.stop();
				
				main.initGame();
			}
			else if (state == 0 && _index == 1)
			{
				// Pulti
				trace('multi');
				
				scene = null;
				removeEventListener(Event.ENTER_FRAME, render);
				background.stop();
			}
			else if (state == 0 && _index == 2)
			{
				// Options
				trace('options');
				changeState(1);
			}
			else if (state == 1 && _index == 0)
			{
				trace('sous-menu keys');
			}
			else if (state == 1 && _index == 1)
			{
				trace('sous-menu display');
			}
			else if (state == 1 && _index == 2)
			{
				trace('sous-menu sound');
			}
		}
		
		private function changeState(new_state : int) : void
		{
			state = new_state;
			spotItem0 = 0;
			scene = new SceneObject3D();
			initMenuItem();
			mainStage.addEventListener(KeyboardEvent.KEY_DOWN, keyboardEvent);
		}
	}
}