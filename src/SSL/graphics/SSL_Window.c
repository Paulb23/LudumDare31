/*-------------------------------------------------------------------------*/
/**
   @file    SSL_window.c
   @author  P. Batty
   @brief   Implements a SDL window and renderer object.

   This module implements a simple window object, a structure containing a
   SDL_window with a SDL_renderer.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/
#include "SSL_window.h"
#include "../misc/SSL_Logger.h"

#include "SDL2/SDL_Image.h"
#include <stdlib.h>
#include <stdint.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Window object.
  @param    title       The title of the window.
  @param    xPosition   The stating X coordinate of the window.
  @param    yPosition   The stating Y coordinate of the window.
  @param    width       Width of the window.
  @param    height      Height of the window.
  @param    resWidth	 The width of the resolution. Enter 0 for same as window width.
  @param    resHeight   The height of the resolution. Enter 0 for same as window height.
  @param    flags       The flags for the window, a mask of any of the following:
               			::SDL_WINDOW_FULLSCREEN, ::SDL_WINDOW_OPENGL,
              				::SDL_WINDOW_HIDDEN,     ::SDL_WINDOW_BORDERLESS,
               			::SDL_WINDOW_RESIZABLE,  ::SDL_WINDOW_MAXIMIZED,
               			::SDL_WINDOW_MINIMIZED,  ::SDL_WINDOW_INPUT_GRABBED
  @return Pointer to a SSL_Window object on successful creation otherwise 0.

  Creates a new SSL_Window object with allocated memory destroy with
  SSL_Window_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Window *SSL_Window_Create(char *title, int xPosition, int yPosition, int width, int height, int resWidth, int resHeight, uint32_t flags) {

	/* allocate memory */
	SSL_Window *window =  malloc(sizeof(SSL_Window));

	/* if we could not allocate memory
	 * Log the error an return 0.
	 */
	if (!window) {
		SSL_Log_Write("Failed to find allocate memory for SSL_Window!");
		return 0;
	}

	/* create the window and render */
	window->window   = SDL_CreateWindow(title, xPosition, yPosition, width, height, flags);
	window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);

	/* check that the window and renderer where created */
	if (window->window == NULL || window->renderer == NULL ) {
		SSL_Log_Write("Failed to create SDL_Window OR SDL_Renderer!");
		return 0;
	}

	/* Initialise them */
	SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetViewport(window->renderer, NULL );

	/* set the resolution */
	int w = width;
	int h = height;

	if (resWidth > 0) {
		w = resWidth;
	}
	if (resHeight > 0) {
		h = resHeight;
	}
	SDL_RenderSetLogicalSize(window->renderer, w, h);

	/* Finally return the SSL_Window */
	return window;
}

/*!--------------------------------------------------------------------------
  @brief    Changes the icon on the window.
  @param    window      The SSL_Window object to change the icon on.
  @param    icon   	 The file path to the icon including file name.extention.
  @return 	 void

  Changes the icon on the SSL_Window object.

\-----------------------------------------------------------------------------*/
void SSL_Window_Set_Icon(SSL_Window *window, char *icon) {
	SDL_SetWindowIcon(window->window, (SDL_Surface *)IMG_Load(icon));
}

/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Window Object.
  @param    window      The SSL_Window object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Window object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Window_Destroy(SSL_Window *window) {

	/* First destroy the window and renderer
	 * then free the memory for the SSL_Window
	 */
	SDL_DestroyWindow(window->window);
	SDL_DestroyRenderer(window->renderer);
	free(window->window);
	free(window->renderer);
	free(window);

	return 1;
}
