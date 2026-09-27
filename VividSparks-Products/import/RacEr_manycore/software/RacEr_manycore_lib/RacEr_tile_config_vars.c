// RacEr_tile_config_vars defines per-tile variables that are used when
// launching execution on a tile. Some variables are only relevant to
// CUDA-Lite programs

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

int __RacEr_x = -1;
int __RacEr_y = -1;
int __RacEr_id = -1;
int __RacEr_grp_org_x = -1;
int __RacEr_grp_org_y = -1;
int __RacEr_grid_dim_x = -1;
int __RacEr_grid_dim_y = -1;
int __RacEr_tile_group_id_x = -1;
int __RacEr_tile_group_id_y = -1;
int __RacEr_tile_group_id = -1;
