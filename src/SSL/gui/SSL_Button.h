/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Button.h
   @author  P. Batty
   @brief   Implements a Button hierarchy

   This module implements a Button inheritance hierarchy for use on the SSL_Interface.

*/
/*--------------------------------------------------------------------------*/

#ifndef BUTTON_H_
#define BUTTON_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"
#include "../graphics/SSL_Image.h"
#include "../graphics/SSL_Font.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    SSL_Element_Type

  An enum contain the different types of widgets

\----------------------------------------------------------------------------*/
typedef enum SSL_Element_type {
	TEXT_BUTTON,				/**< Text Button */
	IMAGE_BUTTON,				/**< Image Button */
	CHECK_BOX					/**< Check box */
} SSL_Element_Type;


/*!--------------------------------------------------------------------------
  @brief    SSL_Element

  This object contains The type of element and it position and size.

  The SSL_Element object is inherited in all gui elements.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Element_ {
	SSL_Element_Type type;		/**< The type of button */
	SDL_Rect	     position;	/**< Position and size of Element */
} SSL_Element;


/*!--------------------------------------------------------------------------
  @brief    SSL_Element

  This object contains The type of element and it position and size.

  The SSL_Element object is inherited in all gui elements.

\----------------------------------------------------------------------------*/
typedef struct _Element_Image_Info {
	SSL_Image *image;					/**< the image to draw with */
	int default_frame;					/**< default frame to draw */
	int hovered_frame;					/**< frame to draw when mouse is hovered */
	int pressed_frame;					/**< frame to draw when the left button is held on the button */
} SSL_Element_Image_Info;


/*!--------------------------------------------------------------------------
  @brief    SSL_Button_Status

  This object contains The various status of the button elements.

  The SSL_Element object is inherited in all button elements.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Button_Status_ {
	int hovered;						/**< is the mouse hovered on the button */
	int clicked;						/**< is the button clicked */
	int pressed;						/**< is the mouse button down on the button */
} SSL_Button_Status;



/*!--------------------------------------------------------------------------
  @brief    SSL_Button_Text_Info

  This object contains information about the text button only

  The _SSL_Button_Text_Info_ object is inherited only in text button elements.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Button_Text_Info_ {
	SSL_Font  *font;					/**< font to draw with */
	SDL_Color  font_color;				/**< color of the font */
	SDL_Color  background_color;		/**< color behind the font */
	char      *text;					/**< text to draw on the button */
} SSL_Button_Text_Info;


/*!--------------------------------------------------------------------------
  @brief    SSL_Text_Button

  This is the text button object, any button that is not drawn from an image
  will be using this object.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Text_Button_ {
	SSL_Element          *button;			/**< Basic button info */
	SSL_Button_Text_Info *button_text_info; /**< text button info */
	SSL_Button_Status    *button_status;	/**< status info */
} SSL_Text_Button;


/*!--------------------------------------------------------------------------
  @brief    SSL_Image_Button

  This is the image button object, any button is drawn from an image
  will be using this object.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Image_Button_ {
	SSL_Element 		   *button;				/**< Basic button info */
	SSL_Element_Image_Info *button_image_info;	/**< image button info */
	SSL_Button_Status 	   *button_status;		/**< status info */
} SSL_Image_Button;


/*!--------------------------------------------------------------------------
  @brief    SSL_Check_Box_Status

  Extra status information for check boxes.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Check_Box_Status_ {
	int active;								/**< is the box ticked */
} SSL_Check_Box_Status;


/*!--------------------------------------------------------------------------
  @brief    SSL_Check_Box_Image_Info

  Extra image information for check boxes.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Check_Box_Image_Info_ {
	int active_frame;						/**< frame to draw when ticked */
} SSL_Check_Box_Image_Info;


/*!--------------------------------------------------------------------------
  @brief    SSL_Check_box

  The check box object any check boxes will be using with object.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Check_Box_ {
	SSL_Element 			 *button;				/**< Basic button info */
	SSL_Element_Image_Info   *button_image_info;	/**< image button info */
	SSL_Button_Status 		 *button_status;		/**< status info */
	SSL_Check_Box_Status 	 *check_box_status;		/**< additional status info */
	SSL_Check_Box_Image_Info *check_box_image_info; /**< additional image info */
} SSL_Check_box;


/*---------------------------------------------------------------------------
                            Function prototypes
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
SSL_Text_Button *SSL_Text_Button_Create(SDL_Rect position, SSL_Font *font, SDL_Color font_color, SDL_Color background_color, char *text);


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
SSL_Image_Button *SSL_Image_Button_Create(SDL_Rect position, SSL_Image *image, int default_frame, int hovered_frame, int pressed_frame);


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
SSL_Check_box *SSL_Check_Box_Create(SDL_Rect position, SSL_Image *image, int default_frame, int hovered_frame, int pressed_frame, int active_frame);


/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Text_Button Object.
  @param    button      The SSL_Text_Button object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Text_Button object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Text_Button_Destroy(SSL_Text_Button *button);

/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Image_Button Object.
  @param    button      The SSL_Image_Button object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Image_Button object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Image_Button_Destroy(SSL_Image_Button *button);

/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Check_box Object.
  @param    button      The SSL_Check_box object to destroy.
  @return 	 1 on success else 0.

  Destroys the SSL_Check_box object.

  If it cannot destroy the object it will return 0.
\-----------------------------------------------------------------------------*/
int SSL_Check_Box_Destroy(SSL_Check_box *button);

#endif
