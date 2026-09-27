// RacEr_tile_config_vars.h defines per-tile variables that are used
// when launching execution on a tile. Some variables are only
// relevant to CUDA-Lite programs. The actual definitions are in
// RacEr_tile_config_vars.c

// __RacEr_x: X coordinate (relative to the group's origin tile)
// __RacEr_y: Y coordinate (relative to the group's origin tile)
// __RacEr_id: Unique ID for each tile in a group
//           (__RacEr_id = __RacEr_y * __RacEr_tile_group_dim_x + __RacEr_x)
// __RacEr_grp_org_x: Global X coordinate of the group origin tile
// __RacEr_grp_org_y: Global Y coordinate of the group origin tile
// __RacEr_grid_dim_x: Global Grid X-Dimension
// __RacEr_grid_dim_y: Global Grid Y-Dimension
// __RacEr_tile_group_id_x: Tile-Group X ID (X-coordinate of current grid iteration)
// __RacEr_tile_group_id_y: Tile-Group Y ID (X-coordinate of current grid iteration)
// __RacEr_tile_group_id: Unique ID for each tile group
//          (__RacEr_tile_group_id = __RacEr_tile_group_id_y * __RacEr_grid_dim_x + __RacEr_tile_group_id_x)

#ifndef __RACER_TILE_CONFIG_VARS_H
#define __RACER_TILE_CONFIG_VARS_H

extern int __RacEr_x;               //The X Cord inside a tile group
extern int __RacEr_y;               //The Y Cord inside a tile group
extern int __RacEr_id;              //The ID of a tile in tile group
extern int __RacEr_grp_org_x;       //The X Cord of the tile group origin
extern int __RacEr_grp_org_y;       //The Y Cord of the tile group origin
extern int __RacEr_grid_dim_x;      //The X Dimensions of the grid of tile groups
extern int __RacEr_grid_dim_y;      //The Y Dimensions of the grid of tile groups
extern int __RacEr_tile_group_id_x; //The X Cord of the tile group within the grid
extern int __RacEr_tile_group_id_y; //The Y Cord of the tile group within the grid
extern int __RacEr_tile_group_id;   //The flat ID of the tile group within the grid

#endif // __RACER_TILE_CONFIG_VARS_H
