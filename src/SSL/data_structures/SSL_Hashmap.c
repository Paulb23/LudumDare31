/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Hashmap.c
   @author  P. Batty
   @brief   Implements a simple hashmap structure

   This module implements a simple hashmap structure, a structure containing a
   key, data and a next element pointer.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "SSL_Hashmap.h"
#include "../misc/SSL_Logger.h"

#include <stdlib.h>


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Creates a new SSL_Hashmap object.
  @return Pointer to a SSL_Hashmap object on successful creation otherwise 0.

  Creates a new SSL_Hashmap object with allocated memory destroy with
  SSL_Hashmap_Destroy.

  If it cannot create the object it will return 0.

\-----------------------------------------------------------------------------*/
SSL_Hashmap *SSL_Hashmap_Create() {

	/* allocate memory */
	SSL_Hashmap *map = malloc(sizeof(SSL_Hashmap));

	/* Check we allocated memory */
	if (!map) {
		SSL_Log_Write("Failed to allocate memory for new Hashmap!");
		SSL_Hashmap_Destroy(map);
		free(map);
		return 0;
	}

	map->map = dictionary_new(0);

	if (!map->map) {
		SSL_Log_Write("Failed to allocate memory for new Hashmap!");
		SSL_Hashmap_Destroy(map);
		free(map);
		return 0;
	}

	map->size = 0;

	/* return hashmap */
	return map;
}


/*!--------------------------------------------------------------------------
  @brief    Adds a element to the SSL_Hashmap
  @param    map		  The SSL_Hashmap to add the data to
  @param    key		  The key to add the data to
  @param    value		  The value to tie to the key
  @return   void

  Adds the data passed in to the key inside the SSL_Hashmap

\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Add(SSL_Hashmap *map, const void *key, const void *value) {
	dictionary_set(map->map, key, value);
	map->size++;
}


/*!--------------------------------------------------------------------------
  @brief    Gets a element in the hashmap
  @param    map		  The SSL_Hashmap to get the data from
  @param    key		  The key to search for
  @return   the value stored at that location else -1

  Returns the value at the given location. NOTE: DOES NOTE CAST TO A TYPE.

\-----------------------------------------------------------------------------*/
void *SSL_Hashmap_Get(SSL_Hashmap *map, const void *key) {
	return dictionary_get(map->map, key, (void *)-1);
}


/*!--------------------------------------------------------------------------
  @brief    Gets a string element in the hashmap
  @param    map		  The SSL_Hashmap to get the data from
  @param    key		  The key to search for
  @return   the value stored at that location else -1

  Returns the data at the given location. as a string.

\-----------------------------------------------------------------------------*/
char *SSL_Hashmap_Get_String(SSL_Hashmap *map, const void *key) {
	return (char *)SSL_Hashmap_Get(map, key);
}

/*!--------------------------------------------------------------------------
  @brief    Gets a int element in the hashmap
  @param    map		  The SSL_Hashmap to get the data from
  @param    key		  The key to search for
  @return   the value stored at that location else -1

  Returns the data at the given location. as a int.

\-----------------------------------------------------------------------------*/
int SSL_Hashmap_Get_Int(SSL_Hashmap *map, const void *key) {
	return atoi(SSL_Hashmap_Get(map, key));
}

/*!--------------------------------------------------------------------------
  @brief    Gets a float element in the hashmap
  @param    map		  The SSL_Hashmap to get the data from
  @param    key		  The key to search for
  @return   the value stored at that location else -1

  Returns the data at the given location. as a float.

\-----------------------------------------------------------------------------*/
float SSL_Hashmap_Get_Float(SSL_Hashmap *map, const void *key) {
	return atof(SSL_Hashmap_Get(map, key));
}


/*!--------------------------------------------------------------------------
  @brief    Gets the size of the hashmap.
  @param    list		  The hashmap to get the size of.
  @return   the size of the hashmap.

  Returns the size or amount of elements in the hashmap.

\-----------------------------------------------------------------------------*/
int SSL_Hashmap_Size(SSL_Hashmap *map) {
	return map->size;
}


/*!--------------------------------------------------------------------------
  @brief    Removes a element in the hashmap
  @param    map		  The SSL_Hashmap to remove the data from
  @param    key		  The key to search for
  @return   void

  remove the value in the SSL_Hashmap.

\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Remove(SSL_Hashmap *map, const void *key) {
	dictionary_unset(map->map, key);

	if (map->size != 0) {
		map->size--;
	}
}


/*!--------------------------------------------------------------------------
  @brief    Destroys the SSL_Hashmap
  @param    map		  The SSL_Hashmap to destroy
  @return   void

  Destroys the SSL_Hashmap.

\-----------------------------------------------------------------------------*/
void SSL_Hashmap_Destroy(SSL_Hashmap *map) {
	dictionary_del(map->map);
}
