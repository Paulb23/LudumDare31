/*-------------------------------------------------------------------------*/
/**
   @file    SSL_Tiled.h
   @author  P. Batty
   @brief   Implements a Tiled .tmx map handler

   This module implements a way to load access and draw .tmx maps
*/
/*--------------------------------------------------------------------------*/

#ifndef SSL_TILED_READER_H_
#define SSL_TILED_READER_H_


/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/


#include "../data_structures/SSL_Hashmap.h"
#include "../data_structures/SSL_List.h"
#include "../graphics/SSL_Image.h"


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


/*!--------------------------------------------------------------------------
  @brief    SSL_Map

  This object contains information about the map such as size, version ect

\----------------------------------------------------------------------------*/
typedef struct _SSL_MAP_ {
	char *version;						/**< Map version 	 	 	*/
	char *orientation;		   			/**< Map orientation	 	*/
	unsigned int map_width;	   			/**< Map width in tiles  	*/
	unsigned int map_height;			/**< Map height in tiles 	*/
	unsigned int tile_width;			/**< Tile width			 	*/
	unsigned int tile_height;			/**< Tile height		 	*/
	unsigned int total_layers;			/**< Total number of layers */
	unsigned int total_tilesets;		/**< Total tilesets			*/
	SSL_Hashmap *properties;			/**< The map properties 	*/
} SSL_Map;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tile_Layer

  This object contains information about each layer

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tile_Layer_ {
	char *name;
	unsigned int width;
	unsigned int height;
	float opacity;
	unsigned char visible;
	int *data;
	SSL_Hashmap *properties;
} SSL_Tile_Layer;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tileset_Info

  This object contains information about the tilesets.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tileset_ {
	unsigned int firstGid;		/**< The id  	      */
	char *name;					/**< The name 	      */
	unsigned int tile_width;	/**< the tile width   */
	unsigned int tile_height;	/**< the tile height  */
	unsigned int spacing;		/**< the tile spacing */
	unsigned int margin;		/**< the tile margin  */
	SSL_Image *image;			/**< the tile image   */
	SSL_Hashmap *properties;	/**< the properties   */
	SSL_List *tiles;			/**< the tiles on set */
} SSL_Tileset;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tile

  This object contains information about the tiles.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tile_ {
	unsigned int id;			/**< The id  	      			   */
	SSL_Image *image;			/**< the image containing the tile */
	SSL_Hashmap *properties;	/**< The properties on this tile   */
} SSL_Tile;


/*!--------------------------------------------------------------------------
  @brief    SSL_Tiled_Map

  The Main object all tiled maps will be made with this object, containing all the
  information on the map stored in it.

  Destroy with SSL_Tiled_Map_Destroy.

\----------------------------------------------------------------------------*/
typedef struct _SSL_Tiled_Map_ {
	SSL_Map	 map;					/**<  The map information */
	SSL_List *tilesets;				/**<  The tilesets */
	SSL_List *layers;				/**<  The layers */
} SSL_Tiled_Map;


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------
  @brief    Loads and creates new Tiled map
  @param    file		 the path to the file
  @param    window       The renderer to use
  @return A SSL_Tiled_Map object

  Loads and creates new Tiled map.
  Destroy with SSL_Tiled_Map_Destroy.

\-----------------------------------------------------------------------------*/
SSL_Tiled_Map *SSL_Tiled_Map_Load(const char *file, SSL_Window *window);


/*!--------------------------------------------------------------------------
  @brief    Draws a loaded map to the screen
  @param    map			 the map to draw
  @param    xOffset		 X Offset to draw the map
  @param    yOffset		 y Offset to draw the map
  @param    window       The window to draw to
  @return A SSL_Tiled_Map object

  Draws the map to the given window.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Draw_Map(SSL_Tiled_Map *map, int xOffset, int yOffset, SSL_Window *window);


/*!--------------------------------------------------------------------------
  @brief    Gets a SSL_Tileset
  @param    map			 map containing the tileset
  @param    gid			 gid of the tile set to get
  @return A SLL_Tileset object else -1

  Gets a SSL_Tileset object from the SSL_Map with the given gid else -1

\-----------------------------------------------------------------------------*/
SSL_Tileset *SSL_Tiled_Get_Tileset(SSL_Tiled_Map *map, int gid);


/*!--------------------------------------------------------------------------
  @brief    Gets the map height in tiles
  @param    map			 map to get the height of
  @return Map height in tiles

  Map height in tiles

\-----------------------------------------------------------------------------*/
unsigned int SSL_Tiled_Get_Height(SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief    Gets the map width in tiles
  @param    map			 map to get the width of
  @return Map width in tiles

  Map width in tiles

\-----------------------------------------------------------------------------*/
unsigned int SSL_Tiled_Get_Width(SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief    Gets the map height in pixels
  @param    map			 map to get the height of
  @return Map height in pixels

  Map height in pixels

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Height_px(SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief    Gets the map width in pixels
  @param    map			 map to get the width of
  @return Map width in pixels

  Map width in pixels

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Width_px(SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief    Gets the tile width in pixels
  @param    map			 map to get the tile width of
  @return Tile width in pixels

  Tile width in pixels

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Tile_Width(SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief    Gets the tile height in pixels
  @param    map			 map to get the tile height of
  @return Tile height in pixels

  Tile height in pixels

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Tile_Height(SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief    Gets the number of layers in the map
  @param    map			 map to get the number of layers
  @return Number of layers

  Number of layers

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Layercount(SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief    Gets the number of tilesets in the map
  @param    map			 map to get the number of tilesets
  @return Number of tilesets

  Number of tilesets

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_Tileset_Count(SSL_Tiled_Map *map);


/*!--------------------------------------------------------------------------
  @brief    Gets the tile id at the location specified
  @param    map			 map to get the number of tile id from
  @param	x			 x position of the tile
  @param	y			 y position of the tile
  @param	layer_index	 layer number position of the tile
  @return tile id at the location specified

  Tile id at the location specified

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_TileId(SSL_Tiled_Map *map, int x, int y, int layer_index);


/*!--------------------------------------------------------------------------
  @brief    Gets the layer index on the map
  @param    map			 map to get the number of layer index from
  @param	name		 name of the layer
  @return layer index of the given layer name else -1

  Layer index of the given layer name else -1

\-----------------------------------------------------------------------------*/
int SSL_Tiled_Get_LayerIndex(SSL_Tiled_Map *map, char *name);

/*!--------------------------------------------------------------------------
  @brief    Destroys the map
  @param    map		The map to destroy
  @return   void

  Destroys the map.

\-----------------------------------------------------------------------------*/
void SSL_Tiled_Map_Destroy(SSL_Tiled_Map *map);


#endif
