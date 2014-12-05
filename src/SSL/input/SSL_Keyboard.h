/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Keyboard.h
   @author  P. Batty
   @brief   Implements a easier way to get information about the keyboard.

   This module implements a easier way to get the keyboard key states.
*/
/*--------------------------------------------------------------------------*/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Gets whether the key is down
  @param    key         SDL_Keycode of the key
  @return true if the key is pressed else false

  Gets whether the key is pressed

\-----------------------------------------------------------------------------*/
int SSL_Keybord_Key_Down(SDL_Keycode key);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the key is down
  @param    key         string version of the key
  @return true if the key is pressed else false

  Gets whether the key is pressed

\-----------------------------------------------------------------------------*/
int SSL_Keybord_Keyname_Down(char *key);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the key is pressed for a single event
  @param    key         SDL_Keycode of the key
  @param    event		The event queue to use
  @return true if the key is pressed else false

  Gets whether the key is pressed

\-----------------------------------------------------------------------------*/
int SSL_Keybord_Key_Pressed(SDL_Keycode key, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the key is pressed for a single event
  @param    key         string version of the key
  @param    event		The event queue to use
  @return true if the key is pressed else false

  Gets whether the key is pressed

\-----------------------------------------------------------------------------*/
int SSL_Keybord_Keyname_Pressed(char *key, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the key is released for a single event
  @param    key         SDL_Keycode of the key
  @param    event		The event queue to use
  @return true if the key is released else false

  Gets whether the key is released

\-----------------------------------------------------------------------------*/
int SSL_Keybord_Key_Released(SDL_Keycode key, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the key is released for a single event
  @param    key         string version of the key
  @param    event		The event queue to use
  @return true if the key is released else false

  Gets whether the key is released

\-----------------------------------------------------------------------------*/
int SSL_Keybord_Keyname_Released(char *key, SDL_Event event);

#endif
