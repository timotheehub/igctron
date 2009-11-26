
package i12.gui
{
	import i12.data.Pool;
	
	import flash.media.Sound;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.BlendMode;
	import flash.display.Sprite;
	import flash.geom.ColorTransform;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	
	import gs.TweenMax;
	import gs.easing.*;
	import gs.events.*;
	
	public class Loader extends Sprite
	{
		/******************************************************************************************/
		/* CONSTANTES                                                                             */
		/******************************************************************************************/
		
		private static var ASSET_COUNT : int = 12;
		
		private static var ASSET_LEFT_MARGIN : Number = 0.2;
		private static var ASSET_RIGHT_MARGIN : Number = 0.2;
		private static var ASSET_BOTTOM_MARGIN : Number = 0.15;

		private static var ASSET_TIMER_DELAY : int = 50;
		
		private static var ASSET_TWEEN_DURATION : Number = 1.0;
		
		private static var ASSET_START_RED : Number = 0.2;
		private static var ASSET_START_GREEN : Number = 0.2;
		private static var ASSET_START_BLUE : Number = 0.4;

		private static var ASSET_DELTA_RED : Number = 0.2;
		private static var ASSET_DELTA_GREEN : Number = 0.2;
		private static var ASSET_DELTA_BLUE : Number = 0.6;
		
		/******************************************************************************************/
		/* PROPERTIES                                                                             */
		/******************************************************************************************/
		
		private var main : Sprite;
		private var pool : Pool;
		
		private var assets : Array;

		/******************************************************************************************/
		/* CONSTRUCTORS                                                                           */
		/******************************************************************************************/

		public function Loader( _main : Sprite, _pool : Pool ) : void
		{
			super();
			
			main = _main;
			pool = _pool;
			
			main.stage.addEventListener( Event.ENTER_FRAME, onLoop );
			
			main.addChild( this );
			
			pool.addEventListener( Event.COMPLETE, onLoadComplete );
			
			assets = new Array( ASSET_COUNT );
					
			var timer : Timer = new Timer( ASSET_TIMER_DELAY );
			
			timer.addEventListener( TimerEvent.TIMER, onShow );
			timer.start();

			var bd : BitmapData = (BitmapData)(pool.getResource( "LoadAsset" ) );
			
			for ( var k : int = 0 ; k < ASSET_COUNT ; k++ )
			{
				var asset : Object = new Object();
				
				asset.bitmap = new Bitmap( bd );
				
				asset.bitmap.x = main.stage.stageWidth * ( ASSET_LEFT_MARGIN + k / ASSET_COUNT * ( 1.0 - ASSET_LEFT_MARGIN - ASSET_RIGHT_MARGIN ) );
				asset.bitmap.y = main.stage.stageHeight * ( 1.0 - ASSET_BOTTOM_MARGIN );
				
				asset.bitmap.scaleX = 0.0;
				asset.bitmap.scaleY = 0.0;
				
				asset.bitmap.alpha = 0.0;

				addChild( asset.bitmap );
				
				assets[k] = asset;
			}
			
			pool.beginLoading();
		}
		
		/******************************************************************************************/
		/* METHODS                                                                                */
		/******************************************************************************************/

		public function dispose() : void
		{
			for ( var k : int = 0 ; k < ASSET_COUNT ; k++ )
			{
				var asset : Object = assets[k];
				
				removeChild( asset.bitmap );
			}
			
			main.removeChild( this );

			main.stage.removeEventListener( Event.ENTER_FRAME, onLoop );
		}
		
		/******************************************************************************************/
		/* EVENTS                                                                                 */
		/******************************************************************************************/

		private function onLoadComplete( e : Event ) : void
		{
			pool.removeEventListener( Event.COMPLETE, onLoadComplete );
			
			var timer : Timer = new Timer( ASSET_TIMER_DELAY );

			timer.addEventListener( TimerEvent.TIMER, onHide );
			timer.start();
		}

		private function onShow( e : TimerEvent ) : void
		{
			var timer : Timer = Timer(e.target);
			
			if ( timer.currentCount < ASSET_COUNT )
			{
				var asset : Object = assets[timer.currentCount];
				
				var x_to : Number = asset.bitmap.x - 0.5 * asset.bitmap.width;
				var y_to : Number = asset.bitmap.y - 0.5 * asset.bitmap.height;
			
				asset.tween = TweenMax.to( asset.bitmap, ASSET_TWEEN_DURATION, { x:x_to, y:y_to, scaleX:1.0, scaleY:1.0, alpha:1.0, ease:Expo.easeOut } );
			}
			else
			{
				timer.removeEventListener( TimerEvent.TIMER, onShow );
				timer.stop();
			}
		}

		private function onHide( e : TimerEvent ) : void
		{
			var timer : Timer = Timer(e.target);
			
			if ( timer.currentCount < ASSET_COUNT )
			{
				var asset : Object = assets[timer.currentCount];
				
				var x_to : Number = asset.bitmap.x + 0.5 * asset.bitmap.width;
				var y_to : Number = asset.bitmap.y + 0.5 * asset.bitmap.height;
			
				asset.tween = TweenMax.to( asset.bitmap, ASSET_TWEEN_DURATION, { x:x_to, y:y_to, scaleX:0.0, scaleY:0.0, alpha:0.0, ease:Expo.easeIn, overwrite:1 } );
				
				if ( timer.currentCount == ASSET_COUNT - 1 )
					asset.tween.addEventListener( TweenEvent.COMPLETE, onHideComplete );
			}
			else
			{
				timer.removeEventListener( TimerEvent.TIMER, onHide );
				timer.stop();
			}
		}

		private function onHideComplete( e : Event ) : void
		{
			var tween : TweenMax = TweenMax(e.target);
			
			tween.removeEventListener( TweenEvent.COMPLETE, onHideComplete );
			
			dispose();
		}

		private function onLoop( e : Event ) : void
		{
			for ( var k : int = 0 ; k < ASSET_COUNT ; k++ )
			{
				var asset : Object = assets[k];
				
				var p : Number = pool.getPercent();
		
				var a : Number = (k + 0) / ASSET_COUNT;
				var b : Number = (k + 1) / ASSET_COUNT;
				
				if ( p < a )
				{
					asset.bitmap.transform.colorTransform = new ColorTransform( ASSET_START_RED, ASSET_START_GREEN, ASSET_START_BLUE, 1.0, 0, 0, 0, 0 );
				}
				else if ( p < b )
				{
					var f : Number = (p - a) / (b - a);
					
					asset.bitmap.transform.colorTransform = new ColorTransform( ASSET_START_RED + ASSET_DELTA_RED * f, ASSET_START_GREEN + ASSET_DELTA_GREEN * f, ASSET_START_BLUE + ASSET_DELTA_BLUE * f, 1.0, 0, 0, 0, 0 );
				}
				else
				{
					asset.bitmap.transform.colorTransform = new ColorTransform( ASSET_START_RED + ASSET_DELTA_RED, ASSET_START_GREEN + ASSET_DELTA_GREEN, ASSET_START_BLUE + ASSET_DELTA_BLUE, 1.0, 0, 0, 0, 0 );
				}
			}
			
		}
	}
}