/*-------------------------------------------------------------------------*/
/**
   @file    SSL_window.h
   @author  P. Batty
   @brief   Implements a SDL window and renderer object.

   This module implements a simple window object, a structure containing a
   SDL_window with a SDL_renderer.
*/
/*--------------------------------------------------------------------------*/

#ifndef SSL_WINDOW_H_
#define SSL_WINDOW_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"
#include <stdint.h>


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    SSL_Window

  This object contains a SDL_Window and a SDL_Renderer. The SSL Window object
  Is used by the library to know what Renderer to draw with on the Window.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Window_ {
	SDL_Window   *window;	    /**< SDL_window */
	SDL_Renderer *renderer;		/**< SDL_renderer */
} SSL_Window;


/*---------------------------------------------------------------------------
                            Function prototypes
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
SSL_Window *SSL_Window_Create(char *title, int xPosition, int yPosition, int width, int height, int resWidth, int resHeight, uint32_t flags);

/*!--------------------------------------------------------------------------
  @brief    Changes the icon on the window.
  @param    window      The SSL_Window object to change the icon on.
  @param    icon   	 The file path to the icon including file name.extention.
  @return 	 void

  Changes the icon on the SSL_Window object.

\-----------------------------------------------------------------------------*/
void SSL_Window_Set_Icon(SSL_Window *window, char *icon);

/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Window Object.
  @param    window      The SSL_Window object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Window object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Window_Destroy(SSL_Window *window);

#endif
