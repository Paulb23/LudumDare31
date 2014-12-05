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

#include "SSL_List.h"
#include "../misc/SSL_Logger.h"

#include <stdlib.h>

/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_List object.
  @return Pointer to a SSL_List object on successful creation otherwise 0.

  Creates a new SSL_List object with allocated memory destroy with
  SSL_List_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_List *SSL_List_Create() {

	/* allocate memory */
	SSL_List *list = malloc(sizeof(SSL_List));

	/* Check we allocated memory */
	if (!list) {
		SSL_Log_Write("Failed to allocate memory for new List!");
		free(list);
		return 0;
	}

	/* point to empty */
	list->data = 0;
	list->next = 0;

	/* return list */
	return list;
}


/*!--------------------------------------------------------------------------
  @brief    Adds a element to the list
  @param    list		  The list to add the data to
  @param    data		  The data to add
  @return   void

  Adds the data passed in to the end of the list

\-----------------------------------------------------------------------------*/
void SSL_List_Add(SSL_List *list, void *data) {

	/* loop until we hit the end of the list */
	while((int)(list->next) != 0 ) list = list->next;

	/* allocate memory */
	SSL_List *tmp = SSL_List_Create();
	tmp->data = malloc(sizeof(data));

	/* fill in the data */
	tmp->data = data;
	tmp->next = 0;

	/* finally we can set the last next to point to the new element */
	list->next = tmp;
}


/*!--------------------------------------------------------------------------
  @brief    Gets a position of the data in the list
  @param    list		  The list to get the data from
  @param    data		  the data to search for
  @return   the position of the data stored at that location else -1

  Returns the position data at the given location.

\-----------------------------------------------------------------------------*/
int SSL_List_Get_Pos(SSL_List *list, void *data) {
	int pos = 0;

	/* loop until we find the data */
	SSL_List *curr = list;
	while (curr->next != 0 && curr->data != data) {
		pos++;
		curr = curr->next;
	}

	/* return the pos if we have the data else -1 */
	return (curr->data == data) ? pos : -1;
}


/*!--------------------------------------------------------------------------
  @brief    Adds a element to the list
  @param    list		  The list to get the data from
  @param    pos		  Position in the list to get the data
  @return   the data stored at that location else -1

  Returns the data at the given location. NOTE: DOES NOTE CAST TO A TYPE.

\-----------------------------------------------------------------------------*/
void *SSL_List_Get(SSL_List *list, int pos) {

	/* loop until we find the pos */
	int i = 0;
	while (i < pos && (int)(list->next) != 0) {
		list = list->next;
		i++;
	}

	/* return */
	return (i == pos) ? list->data : (void *)-1;
}


/*!--------------------------------------------------------------------------
  @brief    Gets a string in the list
  @param    list		  The list to get the data from
  @param    pos		  Position in the list to get the data
  @return   the data stored at that location else -1

  Returns the data at the given location. as a string.

\-----------------------------------------------------------------------------*/
char *SSL_List_Get_String(SSL_List *list, int pos) {
	return (char *) SSL_List_Get(list, pos);
}


/*!--------------------------------------------------------------------------
  @brief    Gets a int in the list
  @param    list		  The list to get the data from
  @param    pos		  Position in the list to get the data
  @return   the data stored at that location else -1

  Returns the data at the given location. as a int.

\-----------------------------------------------------------------------------*/
int SSL_List_Get_Int(SSL_List *list, int pos) {
	return atoi(SSL_List_Get(list, pos));
}


/*!--------------------------------------------------------------------------
  @brief    Gets a float in the list
  @param    list		  The list to get the data from
  @param    pos		  Position in the list to get the data
  @return   the data stored at that location else -1

  Returns the data at the given location. as a float.

\-----------------------------------------------------------------------------*/
float SSL_List_Get_Float(SSL_List *list, int pos) {
	return atof(SSL_List_Get(list, pos));
}


/*!--------------------------------------------------------------------------
  @brief    Gets the size of the list.
  @param    list		  The list to get the size of.
  @return   the size of the list.

  Returns the size or amount of elements in the list.

\-----------------------------------------------------------------------------*/
int SSL_List_Size(SSL_List *list) {
	int size = 0;

	/* loop until we reach the end */;
	while ((int)(list->next) != 0) {
		list = list->next;
		size++;
	}

	/* return the size */
	return size;
}


/*!--------------------------------------------------------------------------
  @brief    Removes a element to the list
  @param    list		  The list to get the data from
  @param    data		  The data to remove
  @return   void

  Removes the data from the list.

\-----------------------------------------------------------------------------*/
void SSL_List_Remove(SSL_List *list, void *data) {

	/* Previous and next pointer to loop through the list */
	SSL_List *pre;
	SSL_List *curr = list;

	/* loop until the end or we find the data */
	while(curr->data != data && curr->next != 0) {
		pre = curr;
		curr = curr->next;
	}

	/* if it does not equal the key we have reached the end */
	if (curr->data != data) {
		return;
	}

	/* else adjust the pointers and free memory */
	pre->next = curr->next;
	free(curr);
}


/*!--------------------------------------------------------------------------
  @brief    Destroys the list
  @return   void

  Destroys the list.

\-----------------------------------------------------------------------------*/
void SSL_List_Destroy(SSL_List *list) {

	/* pointers to loop  */
	SSL_List *pre;
	SSL_List *curr = list;

	/* loop and free each element */
	while(curr->next != 0) {
		pre = curr;
		curr = curr->next;
		free(pre->data);
		free(pre);
	}

	/* free the rest */
	free(pre);
	free(curr);
}
