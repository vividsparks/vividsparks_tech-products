
#include "RacEr_manycore.h"
#include "RacEr_set_tile_x_y.h"

void RacEr_set_tile_x_y()
{
  volatile int *RacEr_x_v = &__RacEr_x;
  volatile int *RacEr_y_v = &__RacEr_y;

  RacEr_remote_int_ptr grp_org_x_p;
  RacEr_remote_int_ptr grp_org_y_p;

  // everybody stores to tile 0,0
  RacEr_remote_store(0,0,RacEr_x_v,0);
  RacEr_remote_store(0,0,RacEr_y_v,0);

  RacEr_wait_while(*RacEr_x_v < 0);
  RacEr_wait_while(*RacEr_y_v < 0);

  if (!*RacEr_x_v && !*RacEr_y_v)
    for (int x = 0; x < RacEr_tiles_X; x++)
      for (int y = 0; y < RacEr_tiles_Y; y++)
      {
        RacEr_remote_store(x,y,RacEr_x_v,x);
        RacEr_remote_store(x,y,RacEr_y_v,y);
      }

  grp_org_x_p = RacEr_remote_ptr_control( __RacEr_x, __RacEr_y, CSR_TGO_X );
  grp_org_y_p = RacEr_remote_ptr_control( __RacEr_x, __RacEr_y, CSR_TGO_Y );

  __RacEr_grp_org_x  = * grp_org_x_p;
  __RacEr_grp_org_y  = * grp_org_y_p;
  __RacEr_id = __RacEr_y * RacEr_tiles_X + __RacEr_x;
  __RacEr_grid_dim_x = 1;
  __RacEr_grid_dim_y = 1;
  __RacEr_tile_group_id_x = 0;
  __RacEr_tile_group_id_y = 0;
  __RacEr_tile_group_id = 0;
}
