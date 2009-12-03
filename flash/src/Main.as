package 
{
	import adobe.utils.CustomActions;
	import flash.display.ActionScriptVersion;
	import flash.display.Scene;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.media.Camera;
	import flash.text.TextField;
	import org.papervision3d.materials.MovieAssetMaterial;
	import org.papervision3d.materials.shadematerials.CellMaterial;
	import org.papervision3d.materials.utils.MaterialsList;
	import org.papervision3d.objects.primitives.Cube;
	import org.papervision3d.objects.primitives.Sphere;
	
	import org.papervision3d.cameras.Camera3D;
	import org.papervision3d.lights.PointLight3D;
	import org.papervision3d.objects.DisplayObject3D;
	import org.papervision3d.render.BasicRenderEngine;
	import org.papervision3d.scenes.Scene3D;
	import org.papervision3d.view.Viewport3D;
	
	import org.papervision3d.materials.shadematerials.GouraudMaterial;
	import org.papervision3d.objects.primitives.Plane;
	
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.media.Sound;
	import flash.utils.getTimer;
	
	import i12.data.Pool;
	import i12.gui.Loader;
	import i12.data.ImageLoader;
	import i12.data.SoundLoader;
	import i12.data.TextLoader;
	
	public class Main extends Sprite 
	{
		[Embed(source="../bin/font/Horsal.ttf", fontFamily="Horseshoes", mimeType="application/x-font-truetype")]
		public static var Horseshoes : Class;
		
		private var pool : Pool;
		private var loader : Loader;

		public static const PLANE_WIDTH:int = 600;
		public static const PLANE_HEIGHT:int = 500;
		
		public static const VEHICLEZ:Number = -8;
		
		private var background : Bitmap;
		
		private var objects : Shape;
		
		public static var game : Game;
		
		private var menu : Menu;
		private var music : Music;
		private var coord : Array = null;
		
		private static const X : int = 0;
		private static const Y : int = 1;
		private static const Z : int = 2;
		
		private var scene:Scene3D;
		private var viewport:Viewport3D;
		private var camere:DynamicCam;//Camera3D;
		private var light:PointLight3D;
		private var renderer:BasicRenderEngine;
		private var universe:DisplayObject3D;
		
		private var plane : Plane;
		private var cellMat : CellMaterial;
		private var vehicleCube : Array = null;
		private var vehicleMat : Array = null;
		
		private var fpsLabel : TextField;
		private var frameCount : Number = 0; // nombre d'images affichées depuis le début de la dernière seconde
		private var timeMark : Number = 0; // marque temporelle du début de la dernière seconde
		private var frameTime : Number = 0; // temps écoulé pour calculer l'avant dernière image
		private var frameMark : Number = 0;
		private var currentFramerate : Number = 0; // nombre d'images calculées durant l'avant dernière seconde
		
		
		public function Main() : void 
		{
			if ( stage != null )
			{
				init();
			}
			else
			{
				addEventListener( Event.ADDED_TO_STAGE, init );
			}
		}
		
		private function init( e : Event = null) : void
		{
			//removeEventListener( Event.ADDED_TO_STAGE, init );
			stage.scaleMode = "exactFit";
			pool = new Pool( stage );

			new ImageLoader( pool, "LoadAsset", "img/sphere.png", true );

			pool.addEventListener( Event.COMPLETE, onPreloadComplete );
			pool.beginLoading();
		}
		
		private function onPreloadComplete( e : Event ) : void // cette fonction est automatiquement appelée lorque le preloading est terminé
		{
			pool.removeEventListener( Event.COMPLETE, onPreloadComplete );

			// chargez vos images ici :
			new ImageLoader( pool, "Menu_Image_0_0", "img/menu_0_0.png", true );
			new ImageLoader( pool, "Menu_Image_0_1", "img/menu_0_1.png", true );
			new ImageLoader( pool, "Menu_Image_0_2", "img/menu_0_2.png", true );

			// chargez vos textes, xml, fichiers de config ici :
			// new TextLoader( pool, "ConfigXML", "config.xml", true );

			// chargez vos sons, musiques ici :
			//new SoundLoader( pool, "SoundSample", "sample.mp3", true );
			new SoundLoader( pool, "Menu_Music_0", "music/menu.mp3", true );
			new SoundLoader( pool, "Game_Music_0", "music/game0.mp3", true );
			new SoundLoader( pool, "Game_Music_1", "music/game1.mp3", true );
			
			pool.addEventListener( Event.COMPLETE, onLoadComplete );

			loader = new Loader( this, pool );
		}

		private function onLoadComplete( e : Event ) : void // cette fonction est automatiquement appelée lorque le loading est terminé
		{
			pool.removeEventListener( Event.COMPLETE, onLoadComplete );
			
			// c'est ici le véritable point d'entrée de votre programme

			initMenu();
		}

		public function getResource( _name : String ) : Object
		{			
			// pour accéder à une ressource chargée de type image :
			// var bmpdata : BitmapData = (BitmapData)(main.getResource( "Logo" ));
			
			// pour accéder à une ressource chargée de type texte :
			// var text : String = (String)(main.getResource( "ConfigXML" ));

			// pour accéder à une ressource chargée de type image :
			// var sound : Sound = (Sound)(main.getResource( "SoundSample" ));
			
			return pool.getResource( _name );
		}
		
		public function initMenu() : void
		{
			music = new Music( this );
			music.menuMusic();
			
			menu = new Menu( this, stage );
		}
		
		public function initGame() : void 
		{
			menu = null;
			music.gameMusic();
			
			viewport = new Viewport3D(0, 0, true);
			viewport.opaqueBackground = 0x00;
			addChild(viewport);
		
			renderer = new BasicRenderEngine();
			
			camere = new DynamicCam( PLANE_WIDTH, PLANE_HEIGHT);
			stage.scaleMode = "exactFit";
			/*
			camere = new Camera3D;// 3D();
			camere.z = -500;
			camere.y = +100;
			//camere.x = +100;
			//camere.zoom = 120;
			camere.orbit( 60, -75, true ); //-90
			*/
			
			

			light = new PointLight3D(true);
			light.x = 500;
			light.z = - 300; 
			scene = new Scene3D();
			
			cellMat = new CellMaterial(light, 0x0000ff,0x0000ff, 2 );
			plane  = new Plane(cellMat, PLANE_WIDTH, PLANE_HEIGHT, 10, 10 );
			plane.z = 20;
			
			universe = new DisplayObject3D();
			universe.addChild(plane);
			scene.addChild(universe);
		
			universe.rotationX += 90;
				
			renderer.renderScene(scene, camere, viewport);

			game = new Game( stage );
			vehicleCube = new Array(0);
			vehicleMat = new Array(0);
			coord = new Array(0);
			
			for ( var i : int = 0 ; i < Main.game.MAX_PLAYERS ; i++ )
			{
				var x:Number = i * 100 + 100;
				var y:Number = 450;
				var z:Number = VEHICLEZ ;
				var color:int;
				
				game.addPlayer( new Player(i, x, y, i > 0 ? false : true, Player.DIRECTION_UP ) );
				
				color = Math.round( Math.random() * 0xFFFF )*256 + Math.round( Math.random()*0x10 );
				
				vehicleMat.push( new CellMaterial(light, color, color, 2) );
				vehicleCube.push( new Cube( new MaterialsList( { all : vehicleMat[i] } ), 15, -2 * VEHICLEZ, 15 ) );
				
				coord[X]= x; coord[Y]=y; coord[Z] = z;
				
				coord = convert3D(coord);
				vehicleCube[i] = moveVehicle( vehicleCube[i], coord );
				
				universe.addChild(vehicleCube[i]);
				
			}
			
			camere.updateCam( vehicleCube[0], game.getPlayer(0) );
			
			fpsLabel = new TextField();
			fpsLabel.textColor = 0xFFFFFF;
			fpsLabel.selectable = false;
			fpsLabel.autoSize = "left";
			fpsLabel.text = "";
			addChild(fpsLabel);
			
			game.ia = new IA ();
			stage.addEventListener( Event.ENTER_FRAME, loop );
		}
		
		private function loop( e : Event = null ) : void
		{
			// Calcul du framerate
			frameCount++;
			
			var time : Number = getTimer();
			
			frameTime = time - frameMark;
			frameMark = time;
			if ( time - timeMark >= 1000.0 )
			{
				currentFramerate = 1000.0 * frameCount / (time - timeMark);
				
				timeMark = time;

				frameCount = 0;
				
				if ( fpsLabel != null )
				{
					fpsLabel.text = "FPS : " + Math.round( currentFramerate );
				}
			}
			
			
			game.update();
			
			
			
			for ( var k : int = 0 ; k < game.getPlayerCount() ; k++ )
			{
				var player : Player = game.getPlayer(k);
				
				if( !player.getLife () )
				{
					coord = player.getCoord ();
					
					coord = convert3D(coord); coord[Z] = VEHICLEZ ;
					vehicleCube[k] = moveVehicle( vehicleCube[k], coord );
					drawWall( player, game.getWall(k), k );
					
					if ( k == 0 ) { camere.updateCam( vehicleCube[0], player ) };
				}
				else if ( vehicleCube[k] != null ) // new dead player
				{
					var count:int = (player.wallCount() - 1);
					
					
					universe.removeChild( vehicleCube[k] );
					vehicleCube[k] = null;
					
					
					for ( var t : int = count; t>=0 ; t-- )
					{ universe.removeChild( player.getPlane(t) ); }
					player.cleanPlanes();
				}
			}
			
			renderer.renderScene(scene, camere, viewport);
		}
		
		static public function convert3D ( coord : Array ) : Array
		{
			var converted : Array = new Array(0);
			
			converted[X] = coord[X] - PLANE_WIDTH / 2;
			converted[Y] = - coord[Y] + PLANE_HEIGHT / 2;
			converted[Z] = coord[Z];
			
			return converted;
		}
		
		private function moveVehicle ( vehicle:Cube, coord:Array ) : Cube
		{
			vehicle.x = coord[X];
			vehicle.y = coord[Y];
			vehicle.z = coord[Z];
			
			return vehicle;
		}
		
		public function drawWall( player : Player, wall : Wall, id : Number ) : void
		{
			var count : int = player.wallCount()
			var lastSeg : Segment = wall.getSegment( wall.getSegmentCount() - 1 );
			
			if ( count > 0 )
			{
				if ( count == wall.getSegmentCount() ) // si pas de nouveau segment : MAJ du dernier
				{	
					universe.removeChild( player.lastPlane() );
					universe.addChild( player.changeLast( segToPlane( lastSeg, id ) ) );
				}
				else
				{
					universe.addChild( player.addPlane( segToPlane( lastSeg, id ) ) );		
				}
			}
			else
			{
				universe.addChild( player.addPlane( segToPlane( lastSeg, id ) ) );
			}
		}
		
		public function segToPlane( seg : Segment, id : int ) : Plane
		{
			var plane:Plane;
			
			//trace('x0 : ' + seg.x0 + ' , x1 : ' + seg.x1 );
			
			if ( seg.x0 == seg.x1 )
			{	
				plane = new Plane( vehicleMat[id] , Math.abs(seg.y1 - seg.y0), -2*VEHICLEZ );
				
				plane.x = seg.x0 - PLANE_WIDTH / 2;
				plane.y = -(seg.y1 + seg.y0 - PLANE_HEIGHT) / 2 ;
				plane.z = VEHICLEZ;
				plane.rotationX = -90;
				plane.rotationZ = 90;
			}
			else
			{
				plane = new Plane ( vehicleMat[id], Math.abs(seg.x1 - seg.x0),-2*VEHICLEZ );
				plane.rotationX = -90;
				plane.x = (seg.x1 + seg.x0 - PLANE_WIDTH) / 2 ;
				plane.y = -seg.y0 + PLANE_HEIGHT / 2;
				plane.z = VEHICLEZ;
			}
			
			return plane;
		}
		
	}
	
}
