
/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "OGLRenderer.h"
#include "X11Window.h"
#include "W32Window.h"
#include "IRenderer.h"
#include "Engine.h"

#ifdef _WIN32
	#include <windows.h>
#endif

/***********************************************************************************/
/** DEBUG                                                                         **/
/***********************************************************************************/

#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************************/

namespace IGC
{

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	OGLRenderer::OGLRenderer( Engine* _engine ) : IRenderer( _engine )
	{
		#ifdef _WIN32
			hDC = 0;
			hRC = 0;
		#endif

		glRenderTexture = 0;

		glFontList = 0;
	}

	OGLRenderer::~OGLRenderer()
	{
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void OGLRenderer::initialize()
	{
#ifdef _WIN32
		static PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
			1,											// Version Number
			PFD_DRAW_TO_WINDOW |						// Format Must Support IWindow
			PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,							// Must Support Double Buffering
			PFD_TYPE_RGBA,								// Request An RGBA Format
			32,											// Select Our Color Depth
			0, 0, 0, 0, 0, 0,							// Color Bits Ignored
			0,											// No Alpha Buffer
			0,											// Shift Bit Ignored
			0,											// No Accumulation Buffer
			0, 0, 0, 0,									// Accumulation Bits Ignored
			16,											// 16Bit Z-Buffer (Depth Buffer)  
			0,											// No Stencil Buffer
			0,											// No Auxiliary Buffer
			PFD_MAIN_PLANE,								// Main Drawing Layer
			0,											// Reserved
			0, 0, 0										// Layer Masks Ignored
		};

		_assert( typeid( *engine->getWindow() ) == typeid( W32Window ), __FILE__, __LINE__,
			"OGLRenderer::initialize() : Invalid window type, W32Window needed." );

		W32Window* window = (W32Window*)engine->getWindow();

		HWND hWnd = window->getHandle();

		hDC = GetDC( hWnd );

		_assert( hDC != 0, __FILE__, __LINE__,
			"OGLRenderer::initialize() : Unable to create a GL Device Context." );

		GLuint pf = ChoosePixelFormat( hDC, &pfd );

		_assert( pf != 0, __FILE__, __LINE__,
			"OGLRenderer::initialize() : Unable to find a suitable Pixel Format." );

		_assert( SetPixelFormat( hDC, pf, &pfd ) == TRUE, __FILE__, __LINE__,
			"OGLRenderer::initialize() : Unable to set the Pixel Format." );

		hRC = wglCreateContext( hDC );

		_assert( pf != 0, __FILE__, __LINE__,
			"OGLRenderer::initialize() : Unable to create a GL Rendering Context." );

		_assert( wglMakeCurrent( hDC, hRC ) == TRUE, __FILE__, __LINE__,
			"OGLRenderer::initialize() : Unable to activate the GL Rendering Context." );
#else
		_assert( typeid( *engine->getWindow() ) == typeid( X11Window ), __FILE__, __LINE__,
			"OGLRenderer::initialize() : Invalid window type, X11Window needed." );

		X11Window* window = (X11Window*)engine->getWindow();

		Display* dpy = window->getDisplay();
		XVisualInfo* vi = window->getVisualInfo();
		IWindow win = window->getWindow();

		ctx = glXCreateContext( dpy, vi, 0, GL_TRUE );

		glXMakeCurrent( dpy, win, ctx );

		window->updateGeometry();
#endif

		int width = engine->getWindow()->getInnerWidth();
		int height = engine->getWindow()->getInnerHeight();

		glViewport( 0, 0, width, height );					// Reset The Current Viewport

		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix

		// Calculate The Aspect Ratio Of The IWindow
		gluPerspective( 90.0f, 1.0f, 0.1f, 100.0f );

		glMatrixMode( GL_MODELVIEW );							// Select The Modelview Matrix
		glLoadIdentity();										// Reset The Modelview Matrix

		glFlush();

		glewInit();

		glShadeModel( GL_SMOOTH );								// Enable Smooth Shading
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );					// Black Background
		glClearDepth( 1.0f );									// Depth Buffer Setup
		glDisable( GL_DEPTH_TEST );								// Enables Depth Testing
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Really Nice Perspective Calculations

		glEnable( GL_TEXTURE_2D );
		glGenTextures( 1, &glRenderTexture );
		glBindTexture( GL_TEXTURE_2D, glRenderTexture );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL );

		glHostTextureData = malloc( width * height * sizeof(uint) );

#ifdef _WIN32
		HFONT font;							// Windows Font ID
		HFONT oldfont;						// Used For Good House Keeping

		glFontList = glGenLists( 96 );		// Storage For 96 Characters

		font = CreateFont
		(
			-12,							// Height Of Font
			0,								// Width Of Font
			0,								// Angle Of Escapement
			0,								// Orientation Angle
			FW_BOLD,						// Font Weight
			FALSE,							// Italic
			FALSE,							// Underline
			FALSE,							// Strikeout
			DEFAULT_CHARSET,				// Character Set Identifier
			OUT_DEFAULT_PRECIS,				// Output Precision
			CLIP_DEFAULT_PRECIS,			// Clipping Precision
			DEFAULT_QUALITY,				// Output Quality
			FF_DONTCARE | DEFAULT_PITCH,	// Family And Pitch
			"Arial"							// Font Name
		);					

		oldfont = (HFONT)SelectObject( hDC, font );		// Selects The Font We Want
		wglUseFontBitmaps( hDC, 32, 96, glFontList );	// Builds 96 Characters Starting At Character 32
		SelectObject( hDC, oldfont );					// Selects The Font We Want
		DeleteObject( font );							// Delete The Font
#else
		glFontList = glGenLists(96);

		/* load a font with a specific name in "Host Portable Character Encoding" */
		XFontStruct* font = XLoadQueryFont( dpy, "-*-helvetica-bold-r-normal--24-*-*-*-p-*-iso8859-1" );

		if ( font == NULL )
		{
			font = XLoadQueryFont( dpy, "fixed" );

			_assert( font != NULL, __FILE__, __LINE__, "OGLRenderer::initialize() : Unable to load any font." );
		}

		glXUseXFont( font->fid, 32, 96, glFontList );

		XFreeFont( dpy, font );
#endif
	}

	void OGLRenderer::finalize()
	{
		glDeleteLists( glFontList, 96 );

		glDeleteTextures( 1, &glRenderTexture );

#ifdef _WIN32
		wglMakeCurrent( NULL, NULL );

		if ( hRC != 0 )
			wglDeleteContext( hRC );

		W32Window* window = (W32Window*)engine->getWindow();

		HWND hWnd = window->getHandle();

		if ( hDC != 0 )
			ReleaseDC( hWnd, hDC );
#else
		if ( ctx )
		{
			X11Window* window = (X11Window*)engine->getWindow();

			Display* dpy = window->getDisplay();

			glXMakeCurrent( dpy, None, NULL );

			glXDestroyContext( dpy, ctx );
		}
#endif
	}

	void OGLRenderer::update()
	{
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		gluPerspective( 90.0f, 1.0f, 0.1f, 100.0f );

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		int width = engine->getWindow()->getInnerWidth();
		int height = engine->getWindow()->getInnerHeight();

		/*glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, glRenderTexture );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, glHostTextureData );

		glColor3f( 1.0f, 1.0f, 1.0f );
		
		glBegin( GL_QUADS );
			glTexCoord2f( 0.0f, 0.0f );
			glVertex3f( -1.0f,  1.0f, -1.0f );
			glTexCoord2f( 1.0f, 0.0f );
			glVertex3f(  1.0f,  1.0f, -1.0f );
			glTexCoord2f( 1.0f, 1.0f );
			glVertex3f(  1.0f, -1.0f, -1.0f );
			glTexCoord2f( 0.0f, 1.0f );
			glVertex3f( -1.0f, -1.0f, -1.0f );
		glEnd();

		glBindTexture( GL_TEXTURE_2D, 0 );
 		glDisable( GL_TEXTURE_2D );*/

 		glTranslatef( 0.0f, 0.0f, -1.0f );

		GLfloat inv_width = 2.0f / (GLfloat)width;
		GLfloat inv_height = 2.0f / (GLfloat)height;

		GLfloat offset = 9.674f * inv_height;

		for ( vector<Label>::iterator it = labels.begin() ; it != labels.end() ; ++it )
		{
			Label label = *it;

			// Pulsing Colors Based On Text Position
			glColor3f( label.r, label.g, label.b );

			// Position The Text On The Screen
			glRasterPos2f( inv_width * (GLfloat)label.x - 1.0f, 1.0f - offset - inv_height * (GLfloat)label.y );

			glPushAttrib( GL_LIST_BIT );												// Pushes The Display List Bits
			glListBase( glFontList - 32 );												// Sets The Base Character to 32
			glCallLists( label.text.length(), GL_UNSIGNED_BYTE, label.text.c_str() );	// Draws The Display List Text
			glPopAttrib();																// Pops The Display List Bits
		}

#ifdef _WIN32
		SwapBuffers( hDC );
#else
		X11Window* window = (X11Window*)engine->getWindow();

		window->swapBuffers();
#endif
	}

	void OGLRenderer::clear( float _r, float _g, float _b, float _depth )
	{
		glClearColor( _r, _g, _b, 1.0f );
		glClearDepth( _depth );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	}

}
