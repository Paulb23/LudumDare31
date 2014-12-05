/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Interface.h
   @author  P. Batty
   @brief   Implements a Interface to put buttons and other gui elements

   This module implements a interface to put gui elements, utilising the SLL_List
   Collection to store them.

*/
/*--------------------------------------------------------------------------*/

#ifndef INTERFACE_H_
#define INTERFACE_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Button.h"
#include "../data_structures/SSL_List.h"
#include "../graphics/SSL_window.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    SSL_Interface

  This object contains a SSL_List collection to store all of the gui elements
  on the interface.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Interface_ {
	SSL_List *buttons;			/**< list of buttons on the interface */
} SSL_Interface;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Interface object.
  @return Pointer to a SSL_Interface object on successful creation otherwise 0.

  Creates a new SSL_Interface object with allocated memory destroy with
  SSL_Interface_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Interface *SSL_Interface_Create();


/*!--------------------------------------------------------------------------
  @brief    Adds a text button to the interface
  @param    interface         Interface to add the button to.
  @param    text_button       The button to add.
  @return void

  Adds a text button to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Add_Text_Button(SSL_Interface *interface, SSL_Text_Button *text_button);


/*!--------------------------------------------------------------------------
  @brief    Adds a image button to the interface
  @param    interface         Interface to add the button to.
  @param    image_button       The button to add.
  @return void

  Adds a image button to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Add_Image_Button(SSL_Interface *interface, SSL_Image_Button *image_Button);


/*!--------------------------------------------------------------------------
  @brief    Adds a check box to the interface
  @param    interface         Interface to add the check box to.
  @param    image_button      The check box to add.
  @return void

  Adds a check box  to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Add_Check_Box(SSL_Interface *interface, SSL_Check_box *check_box);


/*!--------------------------------------------------------------------------
  @brief    Removes a text button to the interface
  @param    interface         Interface to remove the button to.
  @param    text_button       The button to remove.
  @return void

  Removes a text button to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Remove_Text_Button(SSL_Interface *interface, SSL_Text_Button *text_button);

/*!--------------------------------------------------------------------------
  @brief    Removes a image button to the interface
  @param    interface         Interface to remove the button to.
  @param    image_button      The button to remove.
  @return void

  Removes a image button to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Remove_Image_Button(SSL_Interface *interface, SSL_Image_Button *image_button);


/*!--------------------------------------------------------------------------
  @brief    Removes a check box to the interface
  @param    interface         Interface to remove the check box to.
  @param    image_button      The check box to remove.
  @return void

  Removes a check box  to the interface.

\-----------------------------------------------------------------------------*/
void SSL_Interface_Remove_Check_Box(SSL_Interface *interface, SSL_Check_box *check_box);


/*!--------------------------------------------------------------------------
  @brief    Draws all gui elements on the interface.
  @param    interface         Interface to draw
  @param    window    		   The window to draw them on.
  @return void

  Draws all gui elements on the interface.

\-----------------------------------------------------------------------------*/
void interface_draw(SSL_Interface *interface, SSL_Window *window);


/*!--------------------------------------------------------------------------
  @brief    Updates all gui elements on the interface.
  @param    interface         Interface to update
  @param    event    		   The SDL_Event queue to update them with.
  @return void

  interface all gui elements on the interface.

\-----------------------------------------------------------------------------*/
void interface_update(SSL_Interface *interface, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Interface Object.
  @param    image      The SSL_Interface object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Interface object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Interface_Destroy(SSL_Interface *interface);

#endif /* INTERFACE_H_ */
