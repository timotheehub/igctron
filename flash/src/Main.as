package 
{
	import adobe.utils.CustomActions;
	import flash.display.ActionScriptVersion;
	import flash.display.Scene;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
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
	
	public class Main extends Sprite 
	{
		public static const PLANE_WIDTH:int = 1000;
		public static const PLANE_HEIGHT:int = 500;
		
		public static const VEHICLEZ:Number = -5;
		public static const THICKNESS:Number = 2;
		
		private var background : Bitmap;
		
		private var objects : Shape;
		
		private var game : Game;
		
		private var menu : Menu;
		private var music : Music;
		private var coord : Array = null;
		
		private static const X : int = 0;
		private static const Y : int = 1;
		private static const Z : int = 2;
		
		private var scene:Scene3D;
		private var viewport:Viewport3D;
		private var camere:Camera3D;
		private var light:PointLight3D;
		private var renderer:BasicRenderEngine;
		private var universe:DisplayObject3D;
		
		private var plane : Plane;
		private var cellMat : CellMaterial;
		private var vehicleCube : Array = null;
		private var vehicleMat : Array = null;
		
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
			removeEventListener( Event.ADDED_TO_STAGE, init );
			
			music = new Music();
			music.menuMusic();
			
			menu = new Menu( this, stage );
		}
		
		public function initGame( ) : void 
		{
			menu = null;
			music.gameMusic();
			
			viewport = new Viewport3D(0, 0, true);
			viewport.opaqueBackground = 0x00;
			addChild(viewport);
		
			renderer = new BasicRenderEngine();

			camere = new Camera3D();
			camere.z = -250;
			camere.y = +100;
			camere.zoom = 20;
			camere.orbit( 10, -90, true, plane );

			light = new PointLight3D(true);
			light.x = 500;
			light.z = - 300; 
			scene = new Scene3D();
			
			//addChild( background = new Bitmap( new BitmapData( stage.stageWidth, stage.stageHeight, false, 0x00 ) ) );
			cellMat = new CellMaterial(light, 0xffffff,0x0000ff, 3 );
			plane  = new Plane(cellMat, PLANE_WIDTH, PLANE_HEIGHT, 10, 10);
			
			universe = new DisplayObject3D();
			universe.addChild(plane);
			scene.addChild(universe);
		
			universe.localRotationX = -90;
		
			renderer.renderScene(scene, camere,viewport);

			
			//addChild( objects = new Shape() );
			
			game = new Game( stage );
			vehicleCube = new Array(0);
			vehicleMat = new Array(0);
			coord = new Array(0);
			
			for ( var i : int = 0 ; i < Game.MAX_PLAYERS ; i++ )
			{
				var x:Number = i * 100 + 100;
				var y:Number = 450;
				var z:Number = VEHICLEZ;

				game.addPlayer( new Player( game, i, x, y, i > 0 ? false : true, Player.DIRECTION_UP ) );

				vehicleMat.push( new CellMaterial(light, 0x0000ff, 0xff0000, 3) );
				vehicleCube.push( new Cube( new MaterialsList( { all : vehicleMat[i] } ), 15, 15, -2*VEHICLEZ ) );
				
				coord[X]= x; coord[Y]=y; coord[Z] = z;
				
				coord = convert3D(coord);
				vehicleCube[i] = moveVehicle( vehicleCube[i], coord );
				
				/*vehicleCube[i].x = x;
				vehicleCube[i].y = y;
				vehicleCube[i].z = z;
				*/
				
				//moveVehicle( vehicleCube[i], convert3D(coord) );
				
				universe.addChild(vehicleCube[i]);
				
			}
			stage.addEventListener( Event.ENTER_FRAME, loop );
		}
		
		private function loop( e : Event = null ) : void
		{
			game.update();
			
			
			
			for ( var k : int = 0 ; k < game.getPlayerCount() ; k++ )
			{
				var player : Player = game.getPlayer(k);
				
				if( !player.getLife ())
				{
					coord = player.getCoord ();
					
					coord = convert3D(coord); coord[Z] = VEHICLEZ;
					vehicleCube[k] = moveVehicle( vehicleCube[k], coord );
					
					
					//moveVehicle( vehicleCube[k], convert3D(coord) );
					
					/*
					objects.graphics.moveTo( coord [X] - 7, coord [Y] - 7 );
					objects.graphics.lineTo( coord [X] - 7, coord [Y] + 7 );
					objects.graphics.lineTo( coord [X] + 7, coord [Y] + 7 );
					objects.graphics.lineTo( coord [X] + 7, coord [Y] - 7 );
					*/
				}
				else if ( vehicleCube[k] != null )
				{
					universe.removeChild( vehicleCube[k] );
					vehicleCube[k] = null;
					
					for ( var t : int = t; t < player.cubeCount(); t++ )
					{
						universe.removeChild( player.getCube(t) );
					}
				}
			}
			
			/*
			for ( var p : int = 0 ; p < game.getWallCount() ; p++ )
			{
				var wall : Wall = game.getWall(p);
				var wallPlayer : Player = game.getPlayer(p);
				var count : int = wallPlayer.cubeCount()
				var lastSeg : Segment = wall.getSegment( wall.getSegmentCount() - 1 );
				
				trace(count);
				
				if ( count > 0 )
				{
					if ( count == wall.getSegmentCount() ) // si pas de nouveau segment : MAJ du dernier
					{
						universe.removeChild(wallPlayer.removeLastCube());
						universe.addChild( wallPlayer.addCube( segToCube( lastSeg, p ) ) );
					}
					else if ( wall.getSegmentCount() < 2 )
					{
						universe.addChild( wallPlayer.addCube( segToCube( lastSeg, p ) ) );
					}
					else
					{
						universe.removeChild(wallPlayer.removeLastCube());
						universe.addChild( wallPlayer.addCube( segToCube( wall.getSegment( wall.getSegmentCount() - 2 ), p  ) ) );
						universe.addChild( wallPlayer.addCube( segToCube( lastSeg, p ) ) );		
					}
				}
				else
				{
					universe.addChild( wallPlayer.addCube( segToCube( lastSeg, p ) ) );
				}
				
				
			}
			*/
			
			//objects.graphics.endFill();
			
			
			renderer.renderScene(scene, camere,viewport);
		}
		
		private function convert3D ( coord : Array ) : Array
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
		
		public function segToCube( seg : Segment, id : int ) : Cube
		{
			var cube:Cube;
			
			//trace('x0 : ' + seg.x0 + ' , x1 : ' + seg.x1 );
			
			if ( seg.x0 == seg.x1 )
			{	
				cube = new Cube( new MaterialsList( { all : vehicleMat[id] } ), THICKNESS, (seg.y1 - seg.y0), -2*VEHICLEZ );
				cube.x = seg.x0 - PLANE_WIDTH / 2;
				cube.y = -(seg.y1 + seg.y0 - PLANE_HEIGHT) / 2 ;
				cube.z = VEHICLEZ;
			}
			else
			{
				cube = new Cube( new MaterialsList( { all : vehicleMat[id] } ), (seg.x1 - seg.x0), THICKNESS, -2*VEHICLEZ );
				cube.x = (seg.x1 + seg.x0 - PLANE_WIDTH) / 2 ;
				cube.y = -seg.y0 + PLANE_HEIGHT / 2;
				cube.z = VEHICLEZ;
			}
			
			return cube;
		}
		
	}
	
}
