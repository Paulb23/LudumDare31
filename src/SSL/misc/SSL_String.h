/*-------------------------------------------------------------------------*/
/**
   @file    SSL_String.c
   @author  P. Batty
   @brief   Some functions for manipulating strings

   This module implements a some functions for manipulating strings.
*/
/*--------------------------------------------------------------------------*/

#ifndef SSL_STRING_H_
#define SSL_STRING_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------
                            Function prototypes
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
char *SSL_String_Substring(const char *str, int start, int end);


/*!--------------------------------------------------------------------------
  @brief    Gets the last index of a char
  @param    str			 The string to search
  @param    value        The value to look for
  @return int with the last position of the value

  Gets the last index of a char
  ie SSL_String_Last_Index_Of("This is a string", "i") = 14

\-----------------------------------------------------------------------------*/
int SSL_String_Last_Index_Of(const char *str, const char *value);

#endif
