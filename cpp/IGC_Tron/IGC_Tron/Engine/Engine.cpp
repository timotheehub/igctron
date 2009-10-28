
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

/***********************************************************************************/
/** ACCESSEURS                                                                    **/
/***********************************************************************************/

	IWindow* Engine::getWindow()
	{
		return window;
	}

	IRenderer* Engine::getRenderer()
	{
		return renderer;
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
