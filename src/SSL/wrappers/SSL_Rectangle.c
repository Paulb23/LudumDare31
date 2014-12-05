/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Rectangle.c
   @author  P. Batty
   @brief   Simple way to create SDL_Rect objects

   This module implements a simple way to create SDL_Rect objects.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"

#include "SSL_Rectangle.h"

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	 Creates a SDL_Rect Object
  @param    x			  X position of the object.
  @param    y			  y position of the object.
  @param    w			  width of the object.
  @param    h			  height of the object.
  @return 	 A SDL_Rect object or 0 if unsuccessful

   Creates and returns a SDL_Rect Object.


\-----------------------------------------------------------------------------*/
SDL_Rect SSL_Rectangle_Create(const int x, const int y, const int w, const int h) {
	return ( SDL_Rect ) { x, y, w, h };
}
