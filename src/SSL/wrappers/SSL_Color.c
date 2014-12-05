/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Color.h
   @author  P. Batty
   @brief   Simple way to create SDL_Color objects

   This module implements a simple way to create SDL_Color objects.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"

#include "SSL_Color.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	 Creates a SDL_Color Object
  @param    r			  Amount of red 0 - 255.
  @param    g			  Amount of green 0 - 255.
  @param    b			  Amount of blue 0 - 255.
  @param    a			  Amount of alpha
  @return 	 A SDL_Color object or 0 if unsuccessful

   Creates and returns a SDL_Color Object.


\-----------------------------------------------------------------------------*/
SDL_Color SSL_Color_Create(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) {
	return ( SDL_Color ) { r, g, b, a };
}
