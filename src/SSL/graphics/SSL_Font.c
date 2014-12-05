/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Font.c
   @author  P. Batty
   @brief   Implements a TTF_Font lading and drawing.

   This module implements a simple font object, a structure containing a
   TTF_Font, which will be used where ever font is needed.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_window.h"
#include "SSL_Font.h"
#include "../misc/SSL_Logger.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
   @brief	 Creates a new SSL_Font object.
   @param    file         The path to the font including file name.extention.
   @param    size         The font size.
   @return 	 A pointer to a SDL_Font on successful creation otherwise 0.

   Creates a new SSL_Font object with allocated memory destroy with
   SSL_Font_Destroy.

   If it cannot create the object it will return 0

\-----------------------------------------------------------------------------*/
SSL_Font *SSL_Font_Load(char *file, int size) {

	/* Allocate memory */
	SSL_Font *font = malloc(sizeof(SSL_Font));

	/* return if failed allocation */
	if (!font) {
		SSL_Log_Write("Failed to allocate memory, loading font! ");
		return 0;
	}

	/* load the font */
	font->font = TTF_OpenFont(file, size);

	/* return the font */
	return font;
}


/*!--------------------------------------------------------------------------
  @brief    Draws an SSL_Font object to the window.
  @param    x   		  X position on the window to draw.
  @param    y  		  Y position on the window to draw.
  @param    angle        Angle to draw the image at, 0 - 360.
  @param    flip         Flip state of the image, one of the following:
								:: SDL_FLIP_NONE :: SDL_FLIP_HORIZONTAL :: SDL_FLIP_VERTICAL
  @param	 text		  The text to draw.
  @param    font         The SSL_Font object to draw.
  @param    fontColor    The SDL_Color representing the color of the text.
  @param    window       The SSL_Window object to draw the SSL_Font too.
  @return 	 void

  Draws an SSL_Font to the SSL_Window passed.

------------------------------------------------------------------------------*/
void SSL_Font_Draw(int x, int y, int angle, SDL_RendererFlip flip, char *text, SSL_Font *font, SDL_Color fontColor, SSL_Window *window) {

	/* create the font texture */
	SDL_Surface *textSurface = TTF_RenderText_Solid(font->font, text, fontColor);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(window->renderer, textSurface);

	/* check that it's valid */
	if (SDL_QueryTexture(textTexture, NULL, NULL, &textSurface->w, &textSurface->h) != 0) {
		SSL_Log_Write("Failed to create font texture! ");
		return;
	} else {

		/* rectangle to hold the position */
		SDL_Rect offset;
			offset.x = x;
			offset.y = y;
			offset.w = textSurface->w;
			offset.h = textSurface->h;

		/* draw the text */
		SDL_RenderCopyEx( window->renderer, textTexture, NULL, &offset, angle, NULL, flip);
	}

	/* DO NOT REMOVE STOPS MEMORY LEAK */
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

/*!--------------------------------------------------------------------------
   @brief    Destroys the SSL_Font Object.
   @param    font      The SSL_Font object to destroy.
   @return 	 1 on success else 0.

   Destroys the SSL_Font object.

   If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Font_Destroy(SSL_Font *font) {
 free(font->font);
 free(font);

 return 1;
}

