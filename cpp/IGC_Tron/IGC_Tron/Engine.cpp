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

/***********************************************************************************/
/** INCLUSIONS                                                                    **/
/***********************************************************************************/

#include "Engine.h"

#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/time.h>
	#include <unistd.h>
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

	Engine::Engine()
	{
		factory = new Factory( this );

		renderer = NULL;
		window = NULL;

		double time = getTime();
		frameTime = time;
		cycleTime = time;
		totalTime = time;
		
		frameDelta = 0.0;

		cycleCount = 0L;
		totalCount = 0L;

		currentFramerate = 0.0;
		averageFramerate = 0.0;
	}

	Engine::~Engine()
	{
		delete factory;
	}

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	Factory* Engine::getFactory()
	{
		return factory;
	}

	Window* Engine::getWindow()
	{
		return (Window*)window;
	}

	Renderer* Engine::getRenderer()
	{
		return (Renderer*)renderer;
	}

	double Engine::getTime()
	{
		#ifdef _WIN32
			wide counter, frequency;
				
			QueryPerformanceCounter( (LARGE_INTEGER*)&counter );
			QueryPerformanceFrequency( (LARGE_INTEGER*)&frequency );
				
			return (double)counter / (double)frequency;
		#else
			static struct timeval tv;
			static struct timezone tz;

			gettimeofday( &tv, &tz );

			return (double)tv.tv_sec + (double)tv.tv_usec / 1000000;
		#endif
	}

	double Engine::getDelta()
	{
		return frameDelta;
	}

	double Engine::getCurrentFramerate()
	{
		return currentFramerate;
	}

	double Engine::getAverageFramerate()
	{
		return averageFramerate;
	}

/***********************************************************************************/
/** METHODES PUBLIQUES                                                            **/
/***********************************************************************************/

	void Engine::update()
	{
		cycleCount++;

		double time = getTime();

		frameDelta = time - frameTime;
		frameTime = time;

		if ( frameTime - cycleTime >= 1.0 )
		{
			totalCount += cycleCount;

			averageFramerate = (double)totalCount / (frameTime - totalTime);
			currentFramerate = (double)cycleCount / (frameTime - cycleTime);

			cycleTime = frameTime;
			cycleCount = 0L;
		}
	}

}
