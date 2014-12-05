/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Interface.h
   @author  P. Batty
   @brief   Implements a Interface to put buttons and other gui elements

   This module implements a interface to put gui elements, utilising the SLL_List
   Collection to store them.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Interface.h"
#include "../misc/SSL_Logger.h"
#include "../data_structures/SSL_List.h"
#include "../wrappers/SSL_Color.h"
#include "../graphics/SSL_window.h"
#include "../graphics/SSL_Image.h"
#include "../input/SSL_Mouse.h"

#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Interface object.
  @return Pointer to a SSL_Interface object on successful creation otherwise 0.

  Creates a new SSL_Interface object with allocated memory destroy with
  SSL_Interface_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Interface *SSL_Interface_Create() {

	/* Allocate memory */
	SSL_Interface *interface = malloc(sizeof(SSL_Interface));

	/* Return if failed allocation */
	if (!interface) {
		SSL_Log_Write("Failed to allocate memory for new Interface! ");
		return 0;
	}

	/* create the list */
	interface->buttons = SSL_List_Create();

	/* check the list was created else return*/
	if (!interface->buttons) {
		SSL_Log_Write("Failed to allocate memory for new Interface! ");
		return 0;
	}

	/* return the interface */
	return interface;
}


/*!--------------------------------------------------------------------------
  @brief    Adds a text button to the interface
  @param    interface         Interface to add the button to.
  @param    text_button       The button to add.
  @return void

  Adds a text button to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Add_Text_Button(SSL_Interface *interface, SSL_Text_Button *text_button) {
	SSL_List_Add(interface->buttons, text_button);
}


/*!--------------------------------------------------------------------------
  @brief    Adds a image button to the interface
  @param    interface         Interface to add the button to.
  @param    image_button       The button to add.
  @return void

  Adds a image button to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Add_Image_Button(SSL_Interface *interface, SSL_Image_Button *image_button) {
	SSL_List_Add(interface->buttons, image_button);
}


/*!--------------------------------------------------------------------------
  @brief    Adds a check box to the interface
  @param    interface         Interface to add the check box to.
  @param    image_button      The check box to add.
  @return void

  Adds a check box  to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Add_Check_Box(SSL_Interface *interface, SSL_Check_box *check_box) {
	SSL_List_Add(interface->buttons, check_box);
}


/*!--------------------------------------------------------------------------
  @brief    Removes a text button to the interface
  @param    interface         Interface to remove the button to.
  @param    text_button       The button to remove.
  @return void

  Removes a text button to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Remove_Text_Button(SSL_Interface *interface, SSL_Text_Button *text_button) {
	SSL_List_Remove(interface->buttons, text_button);
}


/*!--------------------------------------------------------------------------
  @brief    Removes a image button to the interface
  @param    interface         Interface to remove the button to.
  @param    image_button      The button to remove.
  @return void

  Removes a image button to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Remove_Image_Button(SSL_Interface *interface, SSL_Image_Button *image_button) {
	SSL_List_Remove(interface->buttons, image_button);
}


/*!--------------------------------------------------------------------------
  @brief    Removes a check box to the interface
  @param    interface         Interface to remove the check box to.
  @param    image_button      The check box to remove.
  @return void

  Removes a check box  to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Remove_Check_Box(SSL_Interface *interface, SSL_Check_box *check_box) {
	SSL_List_Remove(interface->buttons, check_box);
}


/*!--------------------------------------------------------------------------
  @brief    Draws all gui elements on the interface.
  @param    interface         Interface to draw
  @param    window    		   The window to draw them on.
  @return void

  Draws all gui elements on the interface.

\-----------------------------------------------------------------------------*/
void interface_draw(SSL_Interface *interface, SSL_Window *window) {
	int i = 1;
	SSL_Text_Button *current_button;
	SSL_Check_box *check_button;
	SSL_Image_Button *image_button;

	while ((current_button = SSL_List_Get(interface->buttons, i)) != (void *)-1) {

		/* if it is a text button*/
		if (current_button->button->type == TEXT_BUTTON) {
				SDL_Color c = SSL_Color_Create(0, 0, 0, 0);
				SDL_GetRenderDrawColor(window->renderer, &c.r, &c.g, &c.b, &c.a);
				SDL_SetRenderDrawColor(window->renderer, current_button->button_text_info->background_color.r, current_button->button_text_info->background_color.g, current_button->button_text_info->background_color.b, current_button->button_text_info->background_color.a);
				SDL_RenderFillRect(window->renderer, &current_button->button->position);
				SDL_SetRenderDrawColor(window->renderer, c.r, c.g, c.b, c.a);
				SSL_Font_Draw(current_button->button->position.x + 5, current_button->button->position.y - 5, 0, SDL_FLIP_NONE, current_button->button_text_info->text, current_button->button_text_info->font, current_button->button_text_info->font_color, window);
		/* else it has an image component */
		} else {

			/* handle check boxes */
			if (current_button->button->type == CHECK_BOX) {
				check_button = (SSL_Check_box *)current_button;

				if (check_button->check_box_status->active) {
					SSL_Image_Draw(check_button->button_image_info->image, check_button->button->position.x, current_button->button->position.y, 0,check_button->check_box_image_info->active_frame, SDL_FLIP_NONE, window);
					break;
				}
			}

			/* handle  image baced buttons */
			image_button = (SSL_Image_Button *)current_button;

			if (current_button->button_status->pressed) {
				SSL_Image_Draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->pressed_frame, SDL_FLIP_NONE, window);
			} else if (current_button->button_status->hovered) {
				SSL_Image_Draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->hovered_frame, SDL_FLIP_NONE, window);
			} else {
				SSL_Image_Draw(image_button->button_image_info->image, image_button->button->position.x, image_button->button->position.y, 0,image_button->button_image_info->default_frame, SDL_FLIP_NONE, window);
			}
		}
	 i++;
	}
}


/*!--------------------------------------------------------------------------
  @brief    Updates all gui elements on the interface.
  @param    interface         Interface to update
  @param    event    		   The SDL_Event queue to update them with.
  @return void

  interface all gui elements on the interface.

\-----------------------------------------------------------------------------*/
void interface_update(SSL_Interface *interface, SDL_Event event) {
	SSL_Text_Button *button;

	int i = 1;

	while ((button = SSL_List_Get(interface->buttons, i)) != (void *)-1) {

		/*hover check */
		if (SSL_Mouse_Hover_In_Area(button->button->position.x, button->button->position.y, button->button->position.w, button->button->position.h, event)) {
				button->button_status->hovered = 1;
		} else {
				button->button_status->hovered = 0;
		}

		// Button is clicked
		if (SSL_Mouse_Left_Clicked_In_Area(button->button->position.x, button->button->position.y, button->button->position.w, button->button->position.h, event)) {
				button->button_status->pressed = 0;

				event.button.button = 0;
				button->button_status->clicked = 1;

		} else {
			button->button_status->clicked = 0;
		}

		/* left button is down */
		if (SSL_Mouse_Left_Down_In_Area(button->button->position.x, button->button->position.y, button->button->position.w, button->button->position.h, event)) {
				event.button.button = 0;
				button->button_status->pressed = 1;
		} else {
				button->button_status->pressed = 0;
		}


		/* handle check boxes */
		if (button->button->type == CHECK_BOX && button->button_status->clicked) {
			SSL_Check_box *box = SSL_List_Get(interface->buttons, i);
			box->check_box_status->active = !box->check_box_status->active;
		}
	 i++;
	}
}


/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Interface Object.
  @param    image      The SSL_Interface object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Interface object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Interface_Destroy(SSL_Interface *interface) {
	int i = 1;
	SSL_Text_Button * current_button;

	/* loop and free all the buttons */
	while ((current_button = SSL_List_Get(interface->buttons, i)) != (void *)-1) {

		if (current_button->button->type == TEXT_BUTTON) {

			SSL_Text_Button_Destroy(current_button);
			free(current_button);
		} else if (current_button->button->type == CHECK_BOX) {

			SSL_Check_Box_Destroy((SSL_Check_box *)current_button);
			free((SSL_Check_box *)current_button);
		} else if (current_button->button->type == IMAGE_BUTTON) {

			SSL_Image_Button_Destroy((SSL_Image_Button *)current_button);
			free((SSL_Image_Button *)current_button);
		}
	 i++;
	}

	/* free the leftovers */
	free(interface);
	free(current_button);

	return 1;
}
