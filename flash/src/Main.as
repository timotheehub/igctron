package 
{
	import adobe.utils.CustomActions;
	import flash.display.ActionScriptVersion;
	import flash.display.Scene;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.media.Camera;
	import flash.text.TextField;
	import org.papervision3d.core.geom.TriangleMesh3D;
	import org.papervision3d.materials.ColorMaterial;
	import org.papervision3d.materials.MovieAssetMaterial;
	import org.papervision3d.materials.shadematerials.CellMaterial;
	import org.papervision3d.materials.special.CompositeMaterial;
	import org.papervision3d.materials.utils.MaterialsList;
	import org.papervision3d.materials.WireframeMaterial;
	import org.papervision3d.objects.parsers.Max3DS;
	import org.papervision3d.objects.primitives.Cube;
	import org.papervision3d.objects.primitives.Sphere;
	import org.papervision3d.render.QuadrantRenderEngine;
	
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
		public static var OPTION_KEY_LEFT 		: uint = 37;
		public static var OPTION_KEY_RIGHT 		: uint = 39;
		public static var OPTION_GRAPHIC_LEVEL	: uint = 5;
		public static var OPTION_MUSIC_LEVEL	: uint = 50;
		public static var OPTION_SOUND_LEVEL 	: uint = 50;
		
		
		[Embed(source="../bin/font/Horsal.ttf", fontFamily="Horseshoes", mimeType="application/x-font-truetype")]
		public static var Horseshoes : Class;
		
		private var pool : Pool;
		private var loader : Loader;

		public static const PLANE_WIDTH:int = 600;
		public static const PLANE_HEIGHT:int = 500;
		public static const NB_GROUND_POLY:Number = 14; //improve if ground disapear
		
		public static const WALL_SMALL_SEG:int = 1;
		public static const WALL_LARGE_SEG:int = 1;//0;
		public static const WALL_THICK:Number = 0.3;
		public static const CUBE_EXCLUDE_FACES:int = Cube.BOTTOM + Cube.RIGHT + Cube.LEFT;
		
		public static const VEHICLEZ:Number = -8;
		public static const Z_OFFSET:Number = 10;
		
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
		private var camera:DynamicCam;//Camera3D;
		private var light:PointLight3D;
		//TODO switch to QuadrantRenderEngine for better quality (lower perf)
		private var renderer:BasicRenderEngine;
		private var universe:DisplayObject3D;
		
		private var plane : Plane;
		private var cellMat : CellMaterial;
		private var colorMat : ColorMaterial;
		private var vehicleCube : Array = null;
		private var vehicleMat : Array = null;
		private var test_vehicle : Max3DS = null;
		
		private var fpsLabel : TextField;
		private var frameCount : Number = 0; // nombre d'images affichées depuis le début de la dernière seconde
		private var timeMark : Number = 0; // marque temporelle du début de la dernière seconde
		private var frameTime : Number = 0; // temps écoulé pour calculer l'avant dernière image
		private var frameMark : Number = 0;
		private var currentFramerate : Number = 0; // nombre d'images calculées durant l'avant dernière seconde
		
		private var cookie_param : Cookie;
		
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
			new ImageLoader( pool, "Menu_Image_1_0", "img/menu_1_0.png", true );
			new ImageLoader( pool, "Menu_Image_1_1", "img/menu_1_1.png", true );
			new ImageLoader( pool, "Menu_Image_1_2", "img/menu_1_2.png", true );

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
			loadCookie();
			
			initMenu();
		}

		private function loadCookie() : void
		{
			cookie_param = new Cookie("igc_tron_param");

			if (cookie_param.read("keybord_left") == "")
				saveKeyLeft();
			else
				Main.OPTION_KEY_LEFT = (uint)(cookie_param.read("keybord_left"));
				
			if (cookie_param.read("keybord_right") == "")
				saveKeyRight();
			else
				Main.OPTION_KEY_RIGHT = (uint)(cookie_param.read("keybord_right"));
			
			if (cookie_param.read("music_level") == "")
				saveMusicLevel();
			else
				Main.OPTION_MUSIC_LEVEL = (uint)(cookie_param.read("music_level"));
			
			if (cookie_param.read("sound_level") == "")
				saveSoundLevel();
			else
				Main.OPTION_SOUND_LEVEL = (uint)(cookie_param.read("sound_level"));
			
			if (cookie_param.read("graphic_level") == "")
				saveGraphicLevel();
			else
				Main.OPTION_GRAPHIC_LEVEL = (uint)(cookie_param.read("graphic_level"));
		}
		
		public function saveKeyLeft(left : uint = 37) : void
		{
			cookie_param.write( "keybord_left", left );
		}
		
		public function saveKeyRight(right : uint = 39) : void
		{
			cookie_param.write( "keybord_right", right );
		}
		
		public function saveSoundLevel(sound_level : uint = 50) : void
		{
			cookie_param.write( "sound_level", sound_level );
		}
		
		public function saveMusicLevel(music_level : uint = 50) : void
		{
			cookie_param.write( "music_level", music_level );
		}
		
		public function saveGraphicLevel(level : uint = 5) : void
		{
			cookie_param.write( "graphic_level", level );
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
			music = new Music(this);
			music.menuMusic();
			
			menu = new Menu(this, stage);
			addChild(menu);
		}
		
		public function initGame() : void 
		{
			menu = null;
			music.gameMusic();
			
			viewport = new Viewport3D(0, 0, true);
			viewport.opaqueBackground = 0x00;
			addChild(viewport);
			
			renderer = new BasicRenderEngine();
			
			camera = new DynamicCam( PLANE_WIDTH, PLANE_HEIGHT, 270, 60, 0, 1500, true, true);
			stage.scaleMode = "exactFit";
			
			/*
			camera = new Camera3D;// 3D();
			camera.z = -500;
			camera.y = +100;
			//camera.x = +100;
			//camera.zoom = 120;
			camera.orbit( 60, -75, true ); //-90
			*/
			
			//Light
			/*light = new PointLight3D(true);
			light.x = 500;
			light.z = - 300; 
			*/
			scene = new Scene3D();
			
			
			//TODO change the numbe of polygones if low ground quality
			//cellMat = new CellMaterial(light, 0x0000ff, 0x0000ff, 2 );
			//cellMat.smooth = false;
			//colorMat = new ColorMaterial( 0x000066);
			var testMat:WireframeMaterial = new WireframeMaterial(0x000066, 1, 1);
			plane  = new Plane(testMat, PLANE_WIDTH, PLANE_HEIGHT, NB_GROUND_POLY, Math.floor( NB_GROUND_POLY * PLANE_HEIGHT / PLANE_WIDTH));// NB_GROUND_POLY );
			plane.z = Z_OFFSET;
			
			universe = new DisplayObject3D();
			universe.addChild(plane);
			scene.addChild(universe);
		
			universe.rotationX += 90;
				
			renderer.renderScene(scene, camera, viewport);

			game = new Game( stage );
			vehicleCube = new Array(0);
			vehicleMat = new Array(0);
			coord = new Array(0);
			
			//TODO TEST IMPORT 3D
			/*
			test_vehicle = new Max3DS();
			test_vehicle.load("3Dmodels/rMBike.3ds");
			test_vehicle.rotationX -= 90;
			test_vehicle.scale = 4;
			coord[X] = 100; coord[Y] = 300; coord[Z] = 0;
			coord = convert3D(coord);
			test_vehicle.x = coord[X];
			test_vehicle.y = coord[Y];
			test_vehicle.z = coord[Z];
			universe.addChild(test_vehicle);
			*/
			
			var x:Number;
			var y:Number;
			var z:Number;
			var color:int;
			
			for ( var i : int = 0 ; i < Main.game.MAX_PLAYERS ; i++ )
			{
				x = i * 100 +100;
				y = 450;
				z = VEHICLEZ;
				
				// static parameters
				game.addPlayer( new Player(i, x, y, i > 0 ? false : true, Player.DIRECTION_UP ) );
				
				color = Math.round( Math.random() * 0xFFFF )*256 + Math.round( Math.random()*0x10 );
				
				vehicleMat.push( new WireframeMaterial(color) );//new ColorMaterial(color) );//new CellMaterial(light, color, color, 2) );
				vehicleCube.push( new Cube( new MaterialsList( { all : vehicleMat[i] } ), 15, -2 * VEHICLEZ, 15 ) );
				
				coord[X]= x; coord[Y]=y; coord[Z] = z;
				
				coord = convert3D(coord);
				vehicleCube[i] = moveVehicle( vehicleCube[i], coord );
				
				universe.addChild(vehicleCube[i]);
				
			}
			
			camera.updateCam( vehicleCube[0], game.getPlayer(0) );
			
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
				
				if( !player.getLife () ) // if not dead
				{
					coord = player.getCoord ();
					
					coord = convert3D(coord); coord[Z] = VEHICLEZ;
					
					vehicleCube[k].x = coord[X];//moveVehicle( vehicleCube[k], coord );
					vehicleCube[k].y = coord[Y];
					vehicleCube[k].z = coord[Z];
					
					drawWall( player, game.getWall(k), k );
					
					//TODO Test static cam
					if ( k == 0 ) { camera.updateCam( vehicleCube[0], player ) };
				}
				else if ( vehicleCube[k] != null ) // if new dead player
				{
					var count:int = (player.wallCount() - 1);
					
					universe.removeChild( vehicleCube[k] );
					delete vehicleCube[k];
					
					for ( var t : int = count; t>=0 ; t-- )
					{ universe.removeChild( player.getPlane(t) ); }
					player.cleanPlanes();
					
				}
			}
			
			renderer.renderScene(scene, camera, viewport);
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
			{ /////////////////////////////TODO
			
			
			
			
			
				if ( count == wall.getSegmentCount() || player.isNew() ) 
				// si pas de nouveau segment : MAJ du dernier
				{	
					universe.removeChild( player.lastPlane() );
					universe.addChild( player.changeLast( segTo3DWall( lastSeg, id)));//, Math.abs(player.getWallLength()/MAX_SEG_LENGTH) ) ) );
				}
				else
				{
					universe.addChild( player.addPlane( segTo3DWall( lastSeg, id)));//, Math.abs(player.getWallLength()/MAX_SEG_LENGTH)  ) ) );
				}
			}
			else
			{	// initialisation
				universe.addChild( player.addPlane( segTo3DWall( lastSeg, id)));//, Math.abs(player.getWallLength()/MAX_SEG_LENGTH) ) ) );
			}
		}
		
		public function segTo3DWall( seg : Segment, id : int) : TriangleMesh3D //, nb_seg : int 
		{
			var wall:TriangleMesh3D;
			
			if ( seg.x0 == seg.x1 )
			{	
				/*
				wall = new Plane( vehicleMat[id] , Math.abs(seg.y1 - seg.y0), -2*VEHICLEZ, WALL_SMALL_SEG, WALL_SMALL_SEG);
				
				wall.x = seg.x0 - PLANE_WIDTH / 2;
				wall.y = -(seg.y1 + seg.y0 - PLANE_HEIGHT) / 2 ;
				wall.z = VEHICLEZ;
				wall.rotationX = -90;
				wall.rotationZ = 90;
				*/
				
				wall = new Cube(  new MaterialsList( { all : vehicleMat[id] }), Math.abs(seg.y1 - seg.y0), WALL_THICK , -2 * VEHICLEZ, WALL_LARGE_SEG, WALL_SMALL_SEG, WALL_SMALL_SEG, 0, CUBE_EXCLUDE_FACES );
				wall.x = seg.x0 - PLANE_WIDTH / 2;
				wall.y = -(seg.y1 + seg.y0 - PLANE_HEIGHT) / 2 ;
				wall.z = VEHICLEZ;
				wall.rotationX = -90;
				wall.rotationZ = 90;
				
				
			}
			else
			{
				/*
				wall = new Plane ( vehicleMat[id], Math.abs(seg.x1 - seg.x0),-2*VEHICLEZ, WALL_SMALL_SEG, WALL_SMALL_SEG );
				wall.rotationX = -90;
				wall.x = (seg.x1 + seg.x0 - PLANE_WIDTH) / 2 ;
				wall.y = -seg.y0 + PLANE_HEIGHT / 2;
				wall.z = VEHICLEZ;
				*/
				
				wall = new Cube(  new MaterialsList( { all : vehicleMat[id] } ), Math.abs(seg.x1 - seg.x0), WALL_THICK , -2 * VEHICLEZ, WALL_LARGE_SEG, WALL_SMALL_SEG, WALL_SMALL_SEG, 0, CUBE_EXCLUDE_FACES  );
				wall.rotationX = -90;
				wall.x = (seg.x1 + seg.x0 - PLANE_WIDTH) / 2 ;
				wall.y = -seg.y0 + PLANE_HEIGHT / 2;
				wall.z = VEHICLEZ;
				
			}
			
			return wall;
		}
		
	}
	
}
