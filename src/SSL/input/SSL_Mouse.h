/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Mouse.h
   @author  P. Batty
   @brief   Implements a easier way to get information about the mouse.

   This module implements a easier way to get the mouse states and whether is
    is inside an area
*/
/*--------------------------------------------------------------------------*/

#ifndef MOUSE_H_
#define MOUSE_H_


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
  @brief    Gets whether the left button is down
  @return true if the left mouse is down else false

  Gets whether the left button is down

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Left_Down();


/*!--------------------------------------------------------------------------
  @brief    Gets whether the right button is down
  @return true if the right mouse is down else false

  Gets whether the right button is down

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Right_Down();


/*!--------------------------------------------------------------------------
  @brief    Gets whether the right middle is down
  @return true if the middle mouse is down else false

  Gets whether the middle button is down

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Middle_Down();


/*!--------------------------------------------------------------------------
  @brief    Gets whether the Left button is clicked#
  @param    event     the SDL_Event queue to use
  @return true if the left button is clicked else false

  Gets whether the  Left button is clicked

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Left_Clicked(SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the right button is clicked
  @param    event     the SDL_Event queue to use
  @return true if the right button is clicked else false

  Gets whether the  right button is clicked

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Right_Clicked(SDL_Event event) ;


/*!--------------------------------------------------------------------------
  @brief    Gets whether the middle button is clicked
  @param    event     the SDL_Event queue to use
  @return true if the middle button is clicked else false

  Gets whether the middle button is clicked

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Middle_Clicked(SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the mouse is in an area
  @param    x         x Location of the area
  @param    y         y Location of the area
  @param    w         width of the area
  @param    h         height of the area
  @param    event     the SDL_Event queue to use
  @return true if the mouse is hovering inside the area else false

  Gets whether the mouse is in the area

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Hover_In_Area(int x, int y, int w, int h, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the left mouse button is down is in an area
  @param    x         x Location of the area
  @param    y         y Location of the area
  @param    w         width of the area
  @param    h         height of the area
  @param    event     the SDL_Event queue to use
  @return true if the left mouse button is down inside the area else false

  Gets whether the left mouse button is down in the area

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Left_Down_In_Area(int x, int y, int w, int h, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the right mouse button is down is in an area
  @param    x         x Location of the area
  @param    y         y Location of the area
  @param    w         width of the area
  @param    h         height of the area
  @param    event     the SDL_Event queue to use
  @return true if the right mouse button is down inside the area else false

  Gets whether the right mouse button is down in the area

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Right_Down_In_Area(int x, int y, int w, int h, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the middle mouse button is down is in an area
  @param    x         x Location of the area
  @param    y         y Location of the area
  @param    w         width of the area
  @param    h         height of the area
  @param    event     the SDL_Event queue to use
  @return true if the middle mouse button is down inside the area else false

  Gets whether the middle mouse button is down in the area

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Middle_Down_In_Area(int x, int y, int w, int h, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the left mouse button is clicked in an area
  @param    x         x Location of the area
  @param    y         y Location of the area
  @param    w         width of the area
  @param    h         height of the area
  @param    event     the SDL_Event queue to use
  @return true if the left mouse button is clicked inside the area else false

  Gets whether the left mouse button is clicked in the area

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Left_Clicked_In_Area(int x, int y, int w, int h, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the right mouse button is clicked in an area
  @param    x         x Location of the area
  @param    y         y Location of the area
  @param    w         width of the area
  @param    h         height of the area
  @param    event     the SDL_Event queue to use
  @return true if the right mouse button is clicked inside the area else false

  Gets whether the right mouse button is clicked in the area

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Right_Clicked_In_Area(int x, int y, int w, int h, SDL_Event event);


/*!--------------------------------------------------------------------------
  @brief    Gets whether the middle mouse button is clicked in an area
  @param    x         x Location of the area
  @param    y         y Location of the area
  @param    w         width of the area
  @param    h         height of the area
  @param    event     the SDL_Event queue to use
  @return true if the middle mouse button is clicked inside the area else false

  Gets whether the middle mouse button is clicked in the area

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Middle_Clicked_In_Area(int x, int y, int w, int h, SDL_Event event);

#endif
