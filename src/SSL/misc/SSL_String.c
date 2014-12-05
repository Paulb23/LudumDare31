/*-------------------------------------------------------------------------*/
/**
   @file    SSL_String.c
   @author  P. Batty
   @brief   Some functions for manipulating strings

   This module implements a some functions for manipulating strings.
*/
/*--------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_String.h"

#include <string.h>
#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/


/*!--------------------------------------------------------------------------
  @brief    Creates a substring from the to points
  @param    str			 The string to extract from
  @param    start		 Start position to extract from
  @param    end			 End position to extract
  @return A char* with the new string

  Creates a substring from the to points
  ie SSL_String_Substring("This is a string", 0, 4) = "This"

\-----------------------------------------------------------------------------*/
char *SSL_String_Substring(const char *str, int start, int end) {
  if (0 > start) return NULL;
  int len = strlen(str);
  // -1 == length of string
  if (-1 == end) end = len;
  if (end <= start) return NULL;
  int diff = end - start;
  if (len == diff) return strdup(str);
  if (len < start) return NULL;
  if (len + 1 < end) return NULL;

  char *res = malloc(sizeof(char) * diff + 1);
  if (NULL == res) return NULL;
  memset(res, '\0', diff + 1);
  strncpy(res, str + start, diff);
  return res;
}


/*!--------------------------------------------------------------------------
  @brief    Gets the last index of a char
  @param    str			 The string to search
  @param    value        The value to look for
  @return int with the last position of the value

  Gets the last index of a char
  ie SSL_String_Last_Index_Of("This is a string", "i") = 14

\-----------------------------------------------------------------------------*/
int SSL_String_Last_Index_Of(const char *str, const char *value) {
	int i = 0;
	int index = 0;
	char *tmp;
	for (tmp = str; *tmp != '\0'; tmp++) {
		if (*tmp == *value) {
			index = i;
			index++;
		}
		i++;
	}

	return index;
}
