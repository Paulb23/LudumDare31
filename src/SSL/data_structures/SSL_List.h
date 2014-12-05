/*-------------------------------------------------------------------------*/
/**
   @file    SSL_List.h
   @author  P. Batty
   @brief   Implements a list collection object.

   This module implements a simple list object, a structure containing a
   and data, and a next pointer.
*/
/*--------------------------------------------------------------------------*/

#ifndef LIST_H_
#define LIST_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    SSL_List

  This object contains a void pointer for the data and next point to the next
  element in the list

\----------------------------------------------------------------------------*/
typedef struct _SSL_List_ {
	void 			  *data;		/**< data in the element */
	struct _SSL_List_ *next;		/**< next element */
} SSL_List;



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_List object.
  @return Pointer to a SSL_List object on successful creation otherwise 0.

  Creates a new SSL_List object with allocated memory destroy with
  SSL_List_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_List *SSL_List_Create();

/*!--------------------------------------------------------------------------
  @brief    Adds a element to the list
  @param    list		  The list to add the data to
  @param    data		  The data to add
  @return   void

  Adds the data passed in to the end of the list

\-----------------------------------------------------------------------------*/
void SSL_List_Add(SSL_List *list, void *data);

/*!--------------------------------------------------------------------------
  @brief    Gets a position of the data in the list
  @param    list		  The list to get the data from
  @param    data		  the data to search for
  @return   the position of the data stored at that location else -1

  Returns the position data at the given location.

\-----------------------------------------------------------------------------*/
int SSL_List_Get_Pos(SSL_List *list, void *data);


/*!--------------------------------------------------------------------------
  @brief    Gets a element in the list
  @param    list		  The list to get the data from
  @param    pos		  Position in the list to get the data
  @return   the data stored at that location else -1

  Returns the data at the given location. NOTE: DOES NOTE CAST TO A TYPE.

\-----------------------------------------------------------------------------*/
void *SSL_List_Get(SSL_List *list, int pos);


/*!--------------------------------------------------------------------------
  @brief    Gets a string in the list
  @param    list		  The list to get the data from
  @param    pos		  Position in the list to get the data
  @return   the data stored at that location else -1

  Returns the data at the given location. as a string.

\-----------------------------------------------------------------------------*/
char *SSL_List_Get_String(SSL_List *list, int pos);

/*!--------------------------------------------------------------------------
  @brief    Gets a int in the list
  @param    list		  The list to get the data from
  @param    pos		  Position in the list to get the data
  @return   the data stored at that location else -1

  Returns the data at the given location. as a int.

\-----------------------------------------------------------------------------*/
int SSL_List_Get_Int(SSL_List *list, int pos);

/*!--------------------------------------------------------------------------
  @brief    Gets a float in the list
  @param    list		  The list to get the data from
  @param    pos		  Position in the list to get the data
  @return   the data stored at that location else -1

  Returns the data at the given location. as a float.

\-----------------------------------------------------------------------------*/
float SSL_List_Get_Float(SSL_List *list, int pos);


/*!--------------------------------------------------------------------------
  @brief    Gets the size of the list.
  @param    list		  The list to get the size of.
  @return   the size of the list.

  Returns the size or amount of elements in the list.

\-----------------------------------------------------------------------------*/
int SSL_List_Size(SSL_List *list);


/*!--------------------------------------------------------------------------
  @brief    Removes a element to the list
  @param    list		  The list to get the data from
  @param    data		  The data to remove
  @return   void

  Removes the data from the list.

\-----------------------------------------------------------------------------*/
void SSL_List_Remove(SSL_List *list, void *data);

/*!--------------------------------------------------------------------------
  @brief    Destroys the list
  @param    list		  The SSL_List to destroy
  @return   void

  Destroys the list.

\-----------------------------------------------------------------------------*/
void SSL_List_Destroy(SSL_List *list);

#endif
