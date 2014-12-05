/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Logger.c
   @author  P. Batty
   @brief   Implements a Logging function.

   This module implements a simple logging function that will
   write a message to a file.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/
#include "SSL_Logger.h"
#include "../SSL_Settings.h"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*!--------------------------------------------------------------------------
  @brief	 Gets the current system time
  @return 	 void string containing the current time.

  Gets the current system and returns a string with the information.


\-----------------------------------------------------------------------------*/
static char *getTime() {
	time_t current_time = time(NULL);
	return ctime(&current_time);
}


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief	 Writes a message to a file
  @param    text		  Text to write.
  @param    ...          printf arguments
  @return 	 void

  Writes a message to a file, in the style of printf.


\-----------------------------------------------------------------------------*/
void SSL_Log_Write(const char *text, ...) {

	/* if we are logging */
	if (LOGGIN) {

		/* open the file */
		FILE *file = fopen(LOG_FILE_PATH, "ab");

		/* if we could not open the file return */
		if (file == NULL) {
			free(file);
			return;
		}

		/* get the current time */
		char* time = getTime();

		/* print out the time */
		fprintf(file, "%s: ", time);

		/* get the argument list */
		va_list arg;

		/* print out the message */
		va_start(arg, text);
		vfprintf(file, text, arg);
		va_end(arg);

		/* print a new line */
		fprintf(file, "\r\n");

		/* close the file and return */
		fclose(file);

		/* free memory */
		free(file);
		free(time);
	}
}
