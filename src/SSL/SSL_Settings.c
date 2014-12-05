/*-------------------------------------------------------------------------*/
/**
   @file    SSL_List.c
   @author  P. Batty
   @brief   Implements a list collection object.

   This module implements a simple list object, a structure containing a
   and data, and a next pointer.
*/
/*--------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Settings.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

char *LOG_FILE_PATH = "../extras/log.txt";		/**< path to the log file */
int LOGGIN = 1;									/**< are we logging  */

int MAX_TICKS_PER_SECOND = 60;			 		/**< max ticks per second */
