/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Button.c
   @author  P. Batty
   @brief   Implements a Button hierarchy

   This module implements a Button inheritance hierarchy for use on the SSL_Interface.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Button.h"
#include "../misc/SSL_Logger.h"
#include "SDL2/SDL.h"
#include "../wrappers/SSL_Color.h"

#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Text_Button object.
  @param    position         SDL_Rect containing the position of the object.
  @param    font         	  SSL_Font object containing the font
  @param    font_color   	  SDL_Color object containing the font color
  @param    background_color SDL_Color object containing the background color
  @param    text 			  The text on the button
  @return Pointer to a SSL_Text_Button object on successful creation otherwise 0.

  Creates a new SSL_Text_Button object with allocated memory destroy with
  SSL_Text_Button_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Text_Button *SSL_Text_Button_Create(SDL_Rect position, SSL_Font *font, SDL_Color font_color, SDL_Color background_color, char *text) {
	SSL_Text_Button *button = malloc(sizeof(SSL_Text_Button));
	button->button = malloc(sizeof(SSL_Element));
	button->button_status = malloc(sizeof(SSL_Button_Status));
	button->button_text_info = malloc(sizeof(SSL_Button_Text_Info));

	button->button->type = TEXT_BUTTON;
	button->button->position = position;
	button->button_status->clicked = 0;
	button->button_status->hovered = 0;
	button->button_status->pressed = 0;
	button->button_text_info->text = text;
	button->button_text_info->font = font;
	button->button_text_info->font_color = font_color;
	button->button_text_info->background_color = background_color;

	return (button) ? button : 0;
}


/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Image_Button object.
  @param    position         SDL_Rect containing the position of the object.
  @param    image         	  SSL_Image object containing the image
  @param    default_frame    Default frame to draw.
  @param    hovered_frame 	  frame when mouse is hovering
  @param    pressed_frame 	  frame to draw when the mouse button is down on the button
  @return Pointer to a SSL_Image_Button object on successful creation otherwise 0.

  Creates a new SSL_Image_Button object with allocated memory destroy with
  SSL_Image_Button_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Image_Button *SSL_Image_Button_Create(SDL_Rect position, SSL_Image *image, int default_frame, int hovered_frame, int pressed_frame) {
	SSL_Image_Button *button = malloc(sizeof(SSL_Image_Button));
	button->button = malloc(sizeof(SSL_Element));
	button->button_status = malloc(sizeof(SSL_Button_Status));
	button->button_image_info = malloc(sizeof(SSL_Element_Image_Info));

	button->button->type = IMAGE_BUTTON;
	button->button->position = position;
	button->button_status->clicked = 0;
	button->button_status->hovered = 0;
	button->button_status->pressed = 0;
	button->button_image_info->image = image;
	button->button_image_info->default_frame = default_frame;
	button->button_image_info->hovered_frame = hovered_frame;
	button->button_image_info->pressed_frame = pressed_frame;

	return (button) ? button : 0;
}


/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Check_box object.
  @param    position         SDL_Rect containing the position of the object.
  @param    image         	  SSL_Image object containing the image
  @param    default_frame    Default frame to draw.
  @param    hovered_frame 	  frame when mouse is hovering
  @param    pressed_frame 	  frame to draw when the mouse button is down on the button
  @param    active_frame 	  frame to draw when the box is ticked
  @return Pointer to a SSL_Check_box object on successful creation otherwise 0.

  Creates a new SSL_Check_box object with allocated memory destroy with
  SSL_Check_Box_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Check_box *SSL_Check_Box_Create(SDL_Rect position, SSL_Image *image, int default_frame, int hovered_frame, int pressed_frame, int active_frame) {
	SSL_Check_box *button = malloc(sizeof(SSL_Check_box));
	button->button = malloc(sizeof(SSL_Element));
	button->button_status = malloc(sizeof(SSL_Button_Status));
	button->check_box_status = malloc(sizeof(SSL_Check_Box_Status));
	button->button_image_info = malloc(sizeof(SSL_Element_Image_Info));
	button->check_box_image_info = malloc(sizeof(SSL_Check_Box_Image_Info));

	button->button->type = CHECK_BOX;
	button->button->position = position;
	button->button_status->clicked = 0;
	button->button_status->hovered = 0;
	button->button_status->pressed = 0;
	button->check_box_status->active = 0;
	button->button_image_info->image = image;
	button->button_image_info->default_frame = default_frame;
	button->button_image_info->hovered_frame = hovered_frame;
	button->button_image_info->pressed_frame = pressed_frame;
	button->check_box_image_info->active_frame = active_frame;

	return (button) ? button : 0;
}


/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Text_Button Object.
  @param    button      The SSL_Text_Button object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Text_Button object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Text_Button_Destroy(SSL_Text_Button *button) {
	free(button->button);
	free(button->button_status);
	free(button->button_text_info);
	free(button);
	return 1;
}

/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Image_Button Object.
  @param    button      The SSL_Image_Button object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Image_Button object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Image_Button_Destroy(SSL_Image_Button *button) {
	free(button->button);
	SDL_DestroyTexture(button->button_image_info->image->Image);
	free(button->button_image_info);
	free(button->button_status);
	free(button);
	return 1;
}

/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Check_box Object.
  @param    button      The SSL_Check_box object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Check_box object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Check_Box_Destroy(SSL_Check_box *button) {
	free(button->button);
	free(button->button_image_info);
	SDL_DestroyTexture(button->button_image_info->image->Image);
	free(button->check_box_image_info);
	free(button->check_box_status);
	free(button);
	return 1;
}

