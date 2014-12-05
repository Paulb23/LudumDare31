/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Keys.c
   @author  P. Batty
   @brief   Allows you to get SDL keys code with a string.

   This module implements a way to get SDL key codes with strings.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SDL2/SDL.h"

#include "SSL_Keys.h"

#include <String.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

const SDL_Scancode _a = SDL_SCANCODE_A;
const SDL_Scancode _b = SDL_SCANCODE_B;
const SDL_Scancode _c = SDL_SCANCODE_C;
const SDL_Scancode _d = SDL_SCANCODE_D;
const SDL_Scancode _e = SDL_SCANCODE_E;
const SDL_Scancode _f = SDL_SCANCODE_F;
const SDL_Scancode _g = SDL_SCANCODE_G;
const SDL_Scancode _h = SDL_SCANCODE_H;
const SDL_Scancode _i = SDL_SCANCODE_I;
const SDL_Scancode _j = SDL_SCANCODE_J;
const SDL_Scancode _k = SDL_SCANCODE_K;
const SDL_Scancode _l = SDL_SCANCODE_L;
const SDL_Scancode _m = SDL_SCANCODE_M;
const SDL_Scancode _n = SDL_SCANCODE_N;
const SDL_Scancode _o = SDL_SCANCODE_O;
const SDL_Scancode _p = SDL_SCANCODE_P;
const SDL_Scancode _q = SDL_SCANCODE_Q;
const SDL_Scancode _r = SDL_SCANCODE_R;
const SDL_Scancode _s = SDL_SCANCODE_S;
const SDL_Scancode _t = SDL_SCANCODE_T;
const SDL_Scancode _u = SDL_SCANCODE_U;
const SDL_Scancode _v = SDL_SCANCODE_V;
const SDL_Scancode _w = SDL_SCANCODE_W;
const SDL_Scancode _x = SDL_SCANCODE_X;
const SDL_Scancode _y = SDL_SCANCODE_Y;
const SDL_Scancode _z = SDL_SCANCODE_Z;

const SDL_Scancode _1 = SDL_SCANCODE_1;
const SDL_Scancode _2 = SDL_SCANCODE_2;
const SDL_Scancode _3 = SDL_SCANCODE_3;
const SDL_Scancode _4 = SDL_SCANCODE_4;
const SDL_Scancode _5 = SDL_SCANCODE_5;
const SDL_Scancode _6 = SDL_SCANCODE_6;
const SDL_Scancode _7 = SDL_SCANCODE_7;
const SDL_Scancode _8 = SDL_SCANCODE_8;
const SDL_Scancode _9 = SDL_SCANCODE_9;
const SDL_Scancode _0 = SDL_SCANCODE_0;


const SDL_Scancode _KP0 = SDL_SCANCODE_KP_0;
const SDL_Scancode _KP1 = SDL_SCANCODE_KP_1;
const SDL_Scancode _KP2 = SDL_SCANCODE_KP_2;
const SDL_Scancode _KP3 = SDL_SCANCODE_KP_3;
const SDL_Scancode _KP4 = SDL_SCANCODE_KP_4;
const SDL_Scancode _KP5 = SDL_SCANCODE_KP_5;
const SDL_Scancode _KP6 = SDL_SCANCODE_KP_6;
const SDL_Scancode _KP7 = SDL_SCANCODE_KP_7;
const SDL_Scancode _KP8 = SDL_SCANCODE_KP_8;
const SDL_Scancode _KP9 = SDL_SCANCODE_KP_9;

const SDL_Scancode _up    = SDL_SCANCODE_UP;
const SDL_Scancode _down  = SDL_SCANCODE_DOWN;
const SDL_Scancode _left  = SDL_SCANCODE_LEFT;
const SDL_Scancode _right = SDL_SCANCODE_RIGHT;

const SDL_Scancode _f1 = SDL_SCANCODE_F1;
const SDL_Scancode _f2 = SDL_SCANCODE_F2;
const SDL_Scancode _f3 = SDL_SCANCODE_F3;
const SDL_Scancode _f4 = SDL_SCANCODE_F4;
const SDL_Scancode _f5 = SDL_SCANCODE_F5;
const SDL_Scancode _f6 = SDL_SCANCODE_F6;
const SDL_Scancode _f7 = SDL_SCANCODE_F7;
const SDL_Scancode _f8 = SDL_SCANCODE_F8;
const SDL_Scancode _f9 = SDL_SCANCODE_F9;
const SDL_Scancode _f10 = SDL_SCANCODE_F10;
const SDL_Scancode _f11 = SDL_SCANCODE_F11;
const SDL_Scancode _f12 = SDL_SCANCODE_F12;

const SDL_Scancode _space = SDL_SCANCODE_SPACE;

const SDL_Scancode _lshift = SDL_SCANCODE_LSHIFT;
const SDL_Scancode _lctrl  = SDL_SCANCODE_LCTRL;
const SDL_Scancode _lalt   = SDL_SCANCODE_LALT;

const SDL_Scancode _rshift = SDL_SCANCODE_RSHIFT;
const SDL_Scancode _rctrl  = SDL_SCANCODE_RCTRL;
const SDL_Scancode _ralt  = SDL_SCANCODE_RALT;


/*!--------------------------------------------------------------------------
  @brief	 Gets the SDL key code from string.
  @param    key		  string variant of the key code
  @return 	 SDL Key code int value else -1.

  Gets the SDL key code from string.


\-----------------------------------------------------------------------------*/
  int GetCode(const char *key) {

	    /* find the key else return -1 */
	    if (strcmp(&key[0], "_a") == 0) {
		    return _a;
	    }
	    if (strcmp(&key[0], "_b") == 0) {
	    	return _b;
	    }
	    if (strcmp(&key[0], "_c") == 0) {
	    	return _c;
	    }
	    if (strcmp(&key[0], "_d") == 0) {
	    	return _d;
	    }
	    if (strcmp(&key[0], "_e") == 0) {
	    	return _e;
	    }
	    if (strcmp(&key[0], "_f") == 0) {
	    	return _f;
	    }
	    if (strcmp(&key[0], "_g") == 0) {
	    	return _g;
	    }
	    if (strcmp(&key[0], "_h") == 0) {
	    	return _h;
	    }
	    if (strcmp(&key[0], "_i") == 0) {
	    	return _i;
	    }
	    if (strcmp(&key[0], "_j") == 0) {
	    	return _j;
	    }
	    if (strcmp(&key[0], "_k") == 0) {
	    	return _k;
	    }
	    if (strcmp(&key[0], "_l") == 0) {
	    	return _l;
	    }
	    if (strcmp(&key[0], "_m") == 0) {
	    	return _m;
	    }
	    if (strcmp(&key[0], "_n") == 0) {
	    	return _n;
	    }
	    if (strcmp(&key[0], "_o") == 0) {
	    	return _o;
	    }
	    if (strcmp(&key[0], "_p") == 0) {
	    	return _p;
	    }
	    if (strcmp(&key[0], "_q") == 0) {
	    	return _q;
	    }
	    if (strcmp(&key[0], "_r") == 0) {
	    	return _r;
	    }
	    if (strcmp(&key[0], "_s") == 0) {
	    	return _s;
	    }
	    if (strcmp(&key[0], "_t") == 0) {
	    	return _t;
	    }
	    if (strcmp(&key[0], "_u") == 0) {
	    	return _u;
	    }
	    if (strcmp(&key[0], "_v") == 0) {
	    	return _v;
	    }
	    if (strcmp(&key[0], "_w") == 0) {
	    	return _w;
	    }
	    if (strcmp(&key[0], "_x") == 0) {
	    	return _x;
	    }
	    if (strcmp(&key[0], "_y") == 0) {
	    	return _y;
	    }
	    if (strcmp(&key[0], "_z") == 0) {
	    	return _z;
	    }

		if (strcmp(&key[0], "_up") == 0) {
		  return _up;
		}
		if (strcmp(&key[0], "_down") == 0) {
		  return _down;
		}
		if (strcmp(&key[0], "_left") == 0) {
			return _left;
		}
		if (strcmp(&key[0], "_right") == 0) {
		  return _right;
		}


		if (strcmp(&key[0], "_0") == 0) {
		  return _0;
		}
		if (strcmp(&key[0], "_1") == 0) {
		  return _1;
		}
		if (strcmp(&key[0], "_2") == 0) {
		  return _2;
		}
	    if (strcmp(&key[0], "_3") == 0) {
		  return _3;
		}
		if (strcmp(&key[0], "_4") == 0) {
		  return _4;
		}
		if (strcmp(&key[0], "_5") == 0) {
		  return _5;
		}
		if (strcmp(&key[0], "_6") == 0) {
		  return _6;
		}
		if (strcmp(&key[0], "_7") == 0) {
		  return _7;
		}
		if (strcmp(&key[0], "_8") == 0) {
		  return _8;
		}
		if (strcmp(&key[0], "_9") == 0) {
		  return _9;
		}

		if (strcmp(&key[0], "_KP0") == 0) {
		  return _KP0;
		}
		if (strcmp(&key[0], "_KP1") == 0) {
		  return _KP1;
	    }
		if (strcmp(&key[0], "_KP2") == 0) {
		  return _KP2;
		}
		if (strcmp(&key[0], "_KP3") == 0) {
		  return _KP3;
		}
		if (strcmp(&key[0], "_KP4") == 0) {
		  return _KP4;
		}
		if (strcmp(&key[0], "_KP5") == 0) {
		  return _KP5;
		}
		if (strcmp(&key[0], "_KP6") == 0) {
		  return _KP6;
		}
		if (strcmp(&key[0], "_KP7") == 0) {
		  return _KP7;
		}
		if (strcmp(&key[0], "_KP8") == 0) {
		  return _KP8;
		}
		if (strcmp(&key[0], "_KP9") == 0) {
		  return _KP9;
		}


		if (strcmp(&key[0], "_f1") == 0) {
		  return _f1;
		}
		if (strcmp(&key[0], "_f2") == 0) {
		  return _f2;
		}
		if (strcmp(&key[0], "_f3") == 0) {
		  return _f3;
		}
		if (strcmp(&key[0], "_f4") == 0) {
		  return _f4;
		}
		if (strcmp(&key[0], "_f5") == 0) {
		  return _f5;
		}
		if (strcmp(&key[0], "_f6") == 0) {
		  return _f6;
		}
		if (strcmp(&key[0], "_f7") == 0) {
		  return _f7;
		}
		if (strcmp(&key[0], "_f8") == 0) {
		  return _f8;
		}
		if (strcmp(&key[0], "_f9") == 0) {
		  return _f9;
		}
		if (strcmp(&key[0], "_f10") == 0) {
		  return _f10;
		}
		if (strcmp(&key[0], "_f11") == 0) {
		  return _f1;
		}
		if (strcmp(&key[0], "_f12") == 0) {
		  return _f12;
		}

		if (strcmp(&key[0], "_space") == 0) {
		  return _space;
		}


		if (strcmp(&key[0], "_lshift") == 0) {
		  return _lshift;
		}
		if (strcmp(&key[0], "_lctrl") == 0) {
		  return _lctrl;
		}
		if (strcmp(&key[0], "_lalt") == 0) {
		  return _lalt;
		}

		if (strcmp(&key[0], "_rshift") == 0) {
		  return _rshift;
		}
		if (strcmp(&key[0], "_rctrl") == 0) {
		  return _rctrl;
		}
		if (strcmp(&key[0], "_ralt") == 0) {
		  return _ralt;
		}

   return -1;
  }
