/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Keys.h
   @author  P. Batty
   @brief   Allows you to get SDL keys code with a string.

   This module implements a way to get SDL key codes with strings.

*/
/*--------------------------------------------------------------------------*/

#ifndef KEYS_H_
#define KEYS_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

extern const SDL_Scancode _a ;
extern const SDL_Scancode _b ;
extern const SDL_Scancode _c ;
extern const SDL_Scancode _d ;
extern const SDL_Scancode _e ;
extern const SDL_Scancode _f ;
extern const SDL_Scancode _g ;
extern const SDL_Scancode _h ;
extern const SDL_Scancode _i ;
extern const SDL_Scancode _j ;
extern const SDL_Scancode _k ;
extern const SDL_Scancode _l ;
extern const SDL_Scancode _m ;
extern const SDL_Scancode _n ;
extern const SDL_Scancode _o ;
extern const SDL_Scancode _p ;
extern const SDL_Scancode _q ;
extern const SDL_Scancode _r ;
extern const SDL_Scancode _s ;
extern const SDL_Scancode _t ;
extern const SDL_Scancode _u ;
extern const SDL_Scancode _v ;
extern const SDL_Scancode _w ;
extern const SDL_Scancode _x ;
extern const SDL_Scancode _y ;
extern const SDL_Scancode _z ;


extern const SDL_Scancode _0 ;
extern const SDL_Scancode _1 ;
extern const SDL_Scancode _2 ;
extern const SDL_Scancode _3 ;
extern const SDL_Scancode _4 ;
extern const SDL_Scancode _5 ;
extern const SDL_Scancode _6 ;
extern const SDL_Scancode _7 ;
extern const SDL_Scancode _8 ;
extern const SDL_Scancode _9 ;


extern const SDL_Scancode _KP0 ;
extern const SDL_Scancode _KP1 ;
extern const SDL_Scancode _KP2 ;
extern const SDL_Scancode _KP3 ;
extern const SDL_Scancode _KP4 ;
extern const SDL_Scancode _KP5 ;
extern const SDL_Scancode _KP6 ;
extern const SDL_Scancode _KP7 ;
extern const SDL_Scancode _KP8 ;
extern const SDL_Scancode _KP9 ;

extern const SDL_Scancode _up ;
extern const SDL_Scancode _down ;
extern const SDL_Scancode _left ;
extern const SDL_Scancode _right ;

extern const SDL_Scancode _f1 ;
extern const SDL_Scancode _f2 ;
extern const SDL_Scancode _f3 ;
extern const SDL_Scancode _f4 ;
extern const SDL_Scancode _f5 ;
extern const SDL_Scancode _f6 ;
extern const SDL_Scancode _f7 ;
extern const SDL_Scancode _f8 ;
extern const SDL_Scancode _f9 ;
extern const SDL_Scancode _f10 ;
extern const SDL_Scancode _f11 ;
extern const SDL_Scancode _f12 ;

extern const SDL_Scancode _space ;

extern const SDL_Scancode _lshift;
extern const SDL_Scancode _lctrl ;
extern const SDL_Scancode _lalt ;

extern const SDL_Scancode _rshift;
extern const SDL_Scancode _rctrl ;
extern const SDL_Scancode _ralt ;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/


/*!--------------------------------------------------------------------------
  @brief	 Gets the SDL key code from string.
  @param    key		  string variant of the key code
  @return 	 SDL Key code int value else -1.

  Gets the SDL key code from string.


\-----------------------------------------------------------------------------*/
int GetCode(const char *key);

#endif
