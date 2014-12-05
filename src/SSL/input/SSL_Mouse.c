/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Mouse.c
   @author  P. Batty
   @brief   Implements a easier way to get information about the mouse.

   This module implements a easier way to get the mouse states and whether is
    is inside an area
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Mouse.h"
#include "SDL2/SDL.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Gets whether the a point is inside an area
  @param    x         x Location of the area
  @param    y         y Location of the area
  @param    w         width of the area
  @param    h         height of the area
  @param    event     the SDL_Event queue to use
  @return true if the point is inside the area else false

  Gets whether a point is in the area

\-----------------------------------------------------------------------------*/
static int in_area(int x1, int y1, int x2, int y2, int w2, int h2) {
	return ( x1 > x2 ) && ( x1 < x2 + w2 ) && ( y1 > y2 ) && ( y1 < y2 + h2 );
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Gets whether the left button is down
  @return true if the left mouse is down else false

  Gets whether the left button is down

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Left_Down() {
	return (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
}


/*!--------------------------------------------------------------------------
  @brief    Gets whether the right button is down
  @return true if the right mouse is down else false

  Gets whether the right button is down

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Right_Down () {
	return (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
}


/*!--------------------------------------------------------------------------
  @brief    Gets whether the right middle is down
  @return true if the middle mouse is down else false

  Gets whether the middle button is down

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Middle_Down () {
	return (SDL_GetMouseState(NULL,NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
}


/*!--------------------------------------------------------------------------
  @brief    Gets whether the Left button is clicked#
  @param    event     the SDL_Event queue to use
  @return true if the left button is clicked else false

  Gets whether the  Left button is clicked

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Left_Clicked(SDL_Event event) {

	/* check it was a mouse up event */
	if (event.type == SDL_MOUSEBUTTONUP) {

		/* check it was the left button */
		if (event.button.button == SDL_BUTTON_LEFT) {

			/* remove the event and return */
			event.button.button = 0;
			return 1;
		}
	}
	return 0;
}


/*!--------------------------------------------------------------------------
  @brief    Gets whether the right button is clicked
  @param    event     the SDL_Event queue to use
  @return true if the right button is clicked else false

  Gets whether the  right button is clicked

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Right_Clicked(SDL_Event event) {

	/* check it was a mouse up event */
	if (event.type == SDL_MOUSEBUTTONUP) {

		/* check it was the right button */
		if (event.button.button == SDL_BUTTON_RIGHT) {

			/* remove the event and return */
			event.button.button = 0;
			return 1;
		}
	}
	return 0;
}


/*!--------------------------------------------------------------------------
  @brief    Gets whether the middle button is clicked
  @param    event     the SDL_Event queue to use
  @return true if the middle button is clicked else false

  Gets whether the middle button is clicked

\-----------------------------------------------------------------------------*/
int SSL_Mouse_Middle_Clicked(SDL_Event event) {

	/* check it was a mouse up event */
	if (event.type == SDL_MOUSEBUTTONUP) {

		/* check it was the right button */
		if (event.button.button == SDL_BUTTON_MIDDLE) {

			/* remove the event and return */
			event.button.button = 0;
			return 1;
		}
	}
	return 0;
}


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
int SSL_Mouse_Hover_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int mx = event.motion.x;
	int my = event.motion.y;

	/* check if it is in the area */
	if (in_area(mx, my, x, y, w, h)) {
		state = 1;
	}

	/* return */
	return state;
}


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
int SSL_Mouse_Left_Down_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int ex = event.button.x;
	int ey = event.button.y;

	/* if the left button was clicked */
	/* check if it is in the area */
	if (SSL_Mouse_Left_Down()) {
		if (in_area(ex, ey, x, y, w, h)) {
			event.button.button = 0;
			state = 1;
		}
	}

	/* return */
	return state;
}


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
int SSL_Mouse_Right_Down_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int ex = event.button.x;
	int ey = event.button.y;

	/* if the right button was clicked */
	/* check if it is in the area */
	if (SSL_Mouse_Right_Down()) {
		if (in_area(ex, ey, x, y, w, h)) {
			event.button.button = 0;
			state = 1;
		}
	}

	/* return */
	return state;
}


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
int SSL_Mouse_Middle_Down_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int ex = event.button.x;
	int ey = event.button.y;

	/* if the middle button was clicked */
	/* check if it is in the area */
	if (SSL_Mouse_Middle_Down()) {
		if (in_area(ex, ey, x, y, w, h)) {
			event.button.button = 0;
			state = 1;
		}
	}

	/* return */
	return state;
}


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
int SSL_Mouse_Left_Clicked_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int ex = event.button.x;
	int ey = event.button.y;

	/* if the left button was clicked */
	/* check if it is in the area */
	if (SSL_Mouse_Left_Clicked(event)) {
		if (in_area(ex, ey, x, y, w, h)) {
			state = 1;
		}
	}

	/* return */
	return state;
}


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
int SSL_Mouse_Right_Clicked_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int ex = event.button.x;
	int ey = event.button.y;

	/* if the right button was clicked */
	/* check if it is in the area */
	if (SSL_Mouse_Right_Clicked(event)) {
		if (in_area(ex, ey, x, y, w, h)) {
			state = 1;
		}
	}

	/* return */
	return state;
}


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
int SSL_Mouse_Middle_Clicked_In_Area(int x, int y, int w, int h, SDL_Event event) {

	int state = 0;

	/* get mouse x and y */
	int ex = event.button.x;
	int ey = event.button.y;

	/* if the middle button was clicked */
	/* check if it is in the area */
	if (SSL_Mouse_Middle_Clicked(event)) {
		if (in_area(ex, ey, x, y, w, h)) {
			state = 1;
		}
	}

	/* return */
	return state;
}
