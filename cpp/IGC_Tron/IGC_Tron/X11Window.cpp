/**************************************************************************/
/* This file is part of IGC Tron                                          */
/* (c) IGC Software 2009 - 2010                                           */
/* Author : Pierre-Yves GATOUILLAT                                        */
/**************************************************************************/
/* This program is free software: you can redistribute it and/or modify   */
/* it under the terms of the GNU General Public License as published by   */
/* the Free Software Foundation, either version 3 of the License, or      */
/* (at your option) any later version.                                    */
/*                                                                        */
/* This program is distributed in the hope that it will be useful,        */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of         */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          */
/* GNU General Public License for more details.                           */
/*                                                                        */
/* You should have received a copy of the GNU General Public License      */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>.  */
/**************************************************************************/

#ifndef _WIN32

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "X11Window.h"
#include "Engine.h"

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

static int attrListSgl[] =
{
	GLX_RGBA, GLX_RED_SIZE, 4, 
	GLX_GREEN_SIZE, 4, 
	GLX_BLUE_SIZE, 4, 
	GLX_DEPTH_SIZE, 16,
	None
};

static int attrListDbl[] =
{
	GLX_RGBA, GLX_DOUBLEBUFFER, 
	GLX_RED_SIZE, 4, 
	GLX_GREEN_SIZE, 4, 
	GLX_BLUE_SIZE, 4, 
	GLX_DEPTH_SIZE, 16,
	None
};

namespace IGC
{

/***********************************************************************************/
/** CONSTRUCTEURS / DESTRUCTEUR                                                   **/
/***********************************************************************************/

	X11Window::X11Window( Engine* _engine ) : IWindow( _engine )
	{
	}

	X11Window::~X11Window()
	{
		hide();
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

/***********************************************************************************/
/** METHODES PRIVEES                                                              **/
/***********************************************************************************/

	void X11Window::create( bool _fullscreen )
	{
		fullscreen = _fullscreen;

		int best_mode = 0;

		dpy = XOpenDisplay(0);

		screen = DefaultScreen( dpy );

		int vidModeMajorVersion, vidModeMinorVersion;
		XF86VidModeQueryVersion( dpy, &vidModeMajorVersion, &vidModeMinorVersion);

		XF86VidModeModeInfo** modes; int mode_count;
		XF86VidModeGetAllModeLines( dpy,  screen, &mode_count, &modes );

		desk_mode = *modes[0];

		for ( int i = 0 ; i < mode_count ; i++ )
		{
			if ( (modes[i]->hdisplay == width) && (modes[i]->vdisplay == height) )
			{
				best_mode = i;
			}
		}

		int glxMajorVersion, glxMinorVersion;

		glXQueryVersion( dpy, &glxMajorVersion, &glxMinorVersion );

		vi = glXChooseVisual( dpy, screen, attrListDbl );

		if ( vi == NULL )
		{
			vi = glXChooseVisual( dpy, screen, attrListSgl );

			doubleBuffered = False;
		}
		else
		{
			doubleBuffered = True;
		}

		Colormap cmap = XCreateColormap( dpy, RootWindow( dpy, vi->screen ), vi->visual, AllocNone );

		XSetWindowAttributes attr;
		attr.colormap = cmap;
		attr.border_pixel = 0;

		if ( fullscreen )
		{
			XF86VidModeSwitchToMode( dpy, screen, modes[best_mode] );
			XF86VidModeSetViewPoint( dpy, screen, 0, 0 );

			int dpyWidth = modes[best_mode]->hdisplay;
			int dpyHeight = modes[best_mode]->vdisplay;

			XFree( modes );

			attr.override_redirect = True;
			attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;

			win = XCreateWindow( dpy, RootWindow( dpy, vi->screen ),
				0, 0, dpyWidth, dpyHeight, 0, vi->depth, InputOutput, vi->visual,
				CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &attr );

			XWarpPointer( dpy, None,  win, 0, 0, 0, 0, 0, 0 );
			XMapRaised( dpy,  win );
			XGrabKeyboard( dpy,  win, True, GrabModeAsync, GrabModeAsync, CurrentTime );
			XGrabPointer( dpy,  win, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, win, None, CurrentTime );
		}
		else
		{
			attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
			win = XCreateWindow( dpy, RootWindow( dpy, vi->screen ),
				0, 0, width, height, 0, vi->depth, InputOutput, vi->visual,
				CWBorderPixel | CWColormap | CWEventMask, &attr );

			Atom wmDelete = XInternAtom( dpy, "WM_DELETE_WINDOW", True );
			XSetWMProtocols( dpy, win, &wmDelete, 1 );
			XSetStandardPropeigcies( dpy, win, "igc", "igc", None, NULL, 0, NULL );
			XMapRaised( dpy, win );
		}

		active = true;
	}

	void X11Window::destroy()
	{
		if ( fullscreen )
		{
			XF86VidModeSwitchToMode( dpy,  screen, & desk_mode );
			XF86VidModeSetViewPoint( dpy,  screen, 0, 0 );
		}

		XCloseDisplay( dpy );
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void X11Window::show()
	{
		if ( visible ) return;

		visible = true;
	}

	void X11Window::hide()
	{
		if ( !visible ) return;

		visible = false;
	}

	void X11Window::updateGeometry()
	{
		IWindow win_dummy;
		uint border_dummy;

		int x, y;
		uint w, h;    
		uint depth;    

		XGetGeometry( dpy, win, &win_dummy, &x, &y,
						&w, &h, &border_dummy, &depth );

		width = w;
		height = h;
	}

	void X11Window::swapBuffers()
	{
		if ( doubleBuffered )
		{
			glXSwapBuffers( dpy,  win );
		}
	}
}

#endif
