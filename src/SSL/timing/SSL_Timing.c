/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Timing.c
   @author  P. Batty
   @brief   Timing loop for the library

   This module implements timing features for the library

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"
#include "../misc/SSL_Logger.h"
#include "../SSL_Settings.h"
#include <time.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

static int    loaded = 0;	/**< is the library already loaded*/
static int    running = 0;  /**< run until this is false */
static double s_fps = 0;	/**< internal fps counter */
static double s_tick = 0;	/**< internal tick counter */
static float s_delta = 0;	/**< internal delta counter */
static SDL_Thread *thread;	/**< the timer thread */


static int    SSL_Uptime = 0;		/**< Time in seconds since the library was initialised */
static float SSL_Delta = 0;		/**< Time since last update */
static double SSL_Fps = 0;			/**< Frames per second */
static double SSL_Tick = 0;			/**< Tick updates for second */

static int SSL_CanTick = 0;			/**< Can we tick update */


/*!--------------------------------------------------------------------------
  @brief    thread timing loop
  @param    data       required for SDL thread, not used
  @return void

  main timing loop

\-----------------------------------------------------------------------------*/
static int update_time(void *data) {
	long lastTime = SDL_GetTicks();						// last time we updated
	const double ns = 1000.0 / MAX_TICKS_PER_SECOND;	// timer to limit to
	Uint32 timer = SDL_GetTicks();						// current time

	while(running) {									// loop forever
		Uint32 now = SDL_GetTicks();					// get the current time
		s_delta += (now - lastTime) / ns;				// calculate the time passed since our last update
		SSL_Delta = s_delta;							// update the global delta time
		lastTime = now;

		while (s_delta >= 1) {							// loop until we have updated 60 times
			SSL_CanTick = 1;							// update the global can tick update
			s_tick++;									// count the ticks
			s_delta--;									// count down
		}
		s_fps++;										// Increases the frames per second counter
		SSL_CanTick = 0;								// can no longer update

		if (SDL_GetTicks() - timer > 1000) {						// if a second has passed
			timer += 1000;								// Increase the timer
			SSL_Fps = s_fps;							// update the global frames per second counter
			SSL_Tick = s_tick;							// update the global tick counter
			s_fps = 0;									// set frames and ticks back to 0
			s_tick = 0;
			SSL_Uptime += 1;							// Increase the update counter

		}

	SDL_Delay(1);
	}

	return 0;
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Starts the timer package
  @return 1 on success else 0

  Starts the timer package, required before you can use and timing functions

\-----------------------------------------------------------------------------*/
int SSL_Timer_Init() {
	if (!loaded) {
		loaded = 1;
		running = 1;
		thread = SDL_CreateThread(update_time, "Timer", (void *)NULL);

		if (thread == NULL) {
			SSL_Log_Write("Failed to create timing thread!" );
			return 0;
		}
	}

	return 1;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the current time in seconds since the SSL timing library was initialised
  @return seconds since the SSL timing library was initialised

  Gets the time in seconds since the SSL timing library was initialised

\-----------------------------------------------------------------------------*/
int SSL_Get_Uptime() {
	return SSL_Uptime;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the current delta time / time since last update
  @return current delta time

  Gets the current delta time / time since last update

\-----------------------------------------------------------------------------*/
float SSL_Get_Delta() {
	return SSL_Delta;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the current frames per second of the program
  @return current frames per second

  Gets the current frames per second of the program, updates every second

\-----------------------------------------------------------------------------*/
double SSL_Get_Fps() {
	return SSL_Fps;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the current ticks per second of the program
  @return current ticks per second

  Gets the current ticks per second of the program, updates every second

\-----------------------------------------------------------------------------*/
double SSL_Get_Ticks() {
	return SSL_Tick;
}


/*!--------------------------------------------------------------------------
  @brief    Gets weather we should perform and update
  @return 1 if we should update the logic else 0

  Gets weather we should perform and update

\-----------------------------------------------------------------------------*/
int SSL_Get_CanTick() {
	return SSL_CanTick;
}


/*!--------------------------------------------------------------------------
  @brief    Stops the timer package
  @return void

  Stops the timer package.

\-----------------------------------------------------------------------------*/
void SSL_Timer_Stop() {
	loaded = 0;
	running = 0;
	SDL_WaitThread(thread, NULL);
}
