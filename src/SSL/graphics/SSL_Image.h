/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Image.h
   @author  P. Batty
   @brief   Implements a SDL_Texture, Surface, and multiple frames.

   This module implements a simple image object, a structure containing a
   SDL_Texture, with all information, such as size, frame size and amount of frame.
*/
/*--------------------------------------------------------------------------*/

#ifndef SDL_API_IMAGE_H_
#define SDL_API_IMAGE_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"
#include "SSL_Window.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    SSL_Image

  This object contains a SDL_Texture and information about the texture such as,
  size, frame size and amount of frames.

  The SSL Image object is used by the library where it will need to draw images.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Image_ {
		SDL_Texture *Image;				/**< The SDL_Texture 			   */
		int 		 texture_width;		/**< Width of the texture 		   */
	    int 		 texture_height;    /**< Height of the texture 		   */
		int 		 frame_height;		/**< Height of each frame 		   */
		int 		 frame_width;		/**< Width of each frame 		   */
		int 		 amount_of_frames;	/**< Amount of frames in the image */
} SSL_Image;


/*---------------------------------------------------------------------------
                            Function prototypes
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
SSL_Image *SSL_Image_Load(char *file, int frameWidth, int frameHeight, SSL_Window *window);

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
void SSL_Image_Draw(SSL_Image *image, int x, int y, int angle, int frame, SDL_RendererFlip flip, SSL_Window *window);

/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Image Object.
  @param    image      The SSL_Image object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Image object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Image_Destroy(SSL_Image *image);

#endif /* SDL_API_IMAGE_H_ */
