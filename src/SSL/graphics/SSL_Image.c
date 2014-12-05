/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Image.c
   @author  P. Batty
   @brief   Implements a SDL_Texture, Surface, and multiple frames.

   This module implements a simple image object, a structure containing a
   SDL_Texture, with all information, such as size, frame size and amount of frame.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "SSL_Image.h"
#include "SSL_window.h"
#include "../misc/SSL_Logger.h"

#include <stdlib.h>
#include <math.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Loads an image from file and converts it to a texture. ( INTERNAL USE ONLY )
  @param    file         The path to the image including file name.extention.
  @param    image        The SSL_Image object to store the image to.
  @param    window       The SSL_Window Renderer to use.
  @return 	 A pointer to a SDL_Texture.

  Loads an image from a file and updates the SSL_Image structure with the information.

\-----------------------------------------------------------------------------*/
static SDL_Texture *image_load_file(char file[], SSL_Image *image, SSL_Window *window) {

	/* Create surface and texture */
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;

	/* Load the file */
	surface = IMG_Load(file);

	/* if we could load the file  */
	if (surface != NULL) {

		/* remove all white and convert to a texture TODO: FIX REMOVES YELLOW? */
		//SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 255, 255, 255) );
		texture = SDL_CreateTextureFromSurface( window->renderer, surface );

		/* update the image width, height */
		image->texture_height = surface->h;
		image->texture_width = surface->w;

		/* free the surface */
		SDL_FreeSurface( surface );
	}

	/* return the texture */
	return texture;
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Image object.
  @param    file         The path to the image including file name.extention.
  @param    frameWidth   Width of each frame pass 0 for entire image.  		* NOTE: BOTH OR NONE OF
  @param    frameHeight  Height of each frame pass 0 for entire image. 		*       THESE MUST BE PASSED
  @param    window       Window to use.
  @return Pointer to a SSL_Window object on successful creation otherwise 0.

  Creates a new SSL_Image object with allocated memory destroy with
  SSL_Image_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Image *SSL_Image_Load(char *file, int frameWidth, int frameHeight, SSL_Window *window) {

	/* Allocate memory */
	SSL_Image *image = malloc(sizeof(SSL_Image));

	/* return if failed allocation */
	if (!image) {
		SSL_Log_Write("Failed to allocate memory, loading image! ");
		return 0;
	}

	/* actually load the texture */
	image->Image = image_load_file(file, image,window);

	/* update the frame variables */
	image->frame_width = frameWidth;
	image->frame_height = frameHeight;

	/* check texture is valid else return */
	if (SDL_QueryTexture(image->Image, NULL, NULL, &image->texture_width, &image->texture_height) != 0) {
		free(image);
		SSL_Log_Write("Failed to create image texture! ");
		return 0;

	/* Else calculate the amount of frame in the image */
	} else if (frameWidth != 0 && frameHeight != 0) {

		int amountOfColumns = image->texture_width / image->frame_width;
		int amountOfRows    = image->texture_height/ image->frame_height;
		int amountOfFrames  = amountOfColumns * amountOfRows;

		image->amount_of_frames = amountOfFrames;
	} else {
		image->amount_of_frames = 0;
	}

	/* return the image */
	return image;
}

/*!--------------------------------------------------------------------------
  @brief    Draws an SSL_Image object to the window.
  @param    Image        The SSLImage object to draw.
  @param    x   		  X position on the window to draw.
  @param    y  		  Y position on the window to draw.
  @param    angle        Angle to draw the image at, 0 - 360.
  @param    frame        Frame to draw, 0 for whole image.
  @param    flip         Flip state of the image, one of the following:
								:: SDL_FLIP_NONE :: SDL_FLIP_HORIZONTAL :: SDL_FLIP_VERTICAL
  @param    window       The SSL_Window object to draw the SSL_Image too.
  @return 	 void

  Draws an SSL_Image to the SSL_Window passed.

\-----------------------------------------------------------------------------*/
void SSL_Image_Draw(SSL_Image *image, int x, int y, int angle, int frame, SDL_RendererFlip flip, SSL_Window *window) {

		/* image frame, rectangle inside the image to draw */
		SDL_Rect imageFrame;
		imageFrame.x = 0;
		imageFrame.y = 0;
		imageFrame.w = image->texture_width;
		imageFrame.h = image->texture_height;

		/* if they want a frame, not the whole image */
		if (frame != 0) {

			/* Calculate the coordinated of the frame */
			int amountOfColumns = (image->texture_width / image->frame_width);

			imageFrame.w = image->frame_width;
			imageFrame.h = image->frame_height;

			if (frame != 1) {
				imageFrame.y = ((frame - 1) / amountOfColumns) * image->frame_height;
				imageFrame.x = ((frame - 1) % amountOfColumns) * image->frame_width;
			}
		}

		/* rectangle for the location in the window */
		SDL_Rect offset;
		offset.x = x;
		offset.y = y;
		offset.w = image->frame_width;
		offset.h = image->frame_height;

		/* find the centre of the frame */
		SDL_Point centre = {
			imageFrame.w / 2,
			imageFrame.h / 2
		};

		/* draw the image */
		SDL_RenderCopyEx( window->renderer, image->Image, &imageFrame, &offset, angle, &centre, flip);
}

/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Image Object.
  @param    image      The SSL_Image object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Image object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Image_Destroy(SSL_Image *image) {
	SDL_DestroyTexture(image->Image);
	free(image);

 return 1;
}
