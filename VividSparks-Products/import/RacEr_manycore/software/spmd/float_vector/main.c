// This code shows an example use of the RacEr_tile_group_shared_mem primitive.
// RacEr_tile_group_shared_mem declares a tilegroup-shared array with the desired size, that is evenly distributed among tiles in a tilegroup using a specific hash function.
// Access to tilegroup-shared memory is done through RacEr_tile_group_shared_load and RacEr_tile_group_shared_store primitives, that take in the pointer to local variable and the index.





#include "RacEr_manycore.h"
#include "RacEr_set_tile_x_y.h"

#define BARRIER_X_START 		0
#define BARRIER_Y_START 		0

#define BARRIER_X_END			(RacEr_tiles_X - 1)
#define BARRIER_Y_END			(RacEr_tiles_Y - 1)
#define BARRIER_X_NUM			(BARRIER_X_END - BARRIER_X_START +1) 
#define BARRIER_Y_NUM			(BARRIER_Y_END - BARRIER_Y_START +1) 
#define BARRIER_TILES			( BARRIER_X_NUM * BARRIER_Y_NUM )

#define  RACER_BARRIER_DEBUG		1
#define  RACER_TILE_GROUP_X_DIM	BARRIER_X_NUM
#define  RACER_TILE_GROUP_Y_DIM	BARRIER_Y_NUM
#define  RACER_TILE_GROUP_SIZE	(RACER_TILE_GROUP_X_DIM * RACER_TILE_GROUP_Y_DIM)
#include "RacEr_tile_group_barrier.h"

INIT_TILE_GROUP_BARRIER (row_barrier_inst, col_barrier_inst, BARRIER_X_START, BARRIER_X_END, BARRIER_Y_START, BARRIER_Y_END);







////////////////////////////////////////////////////////////////////
int main() {

	RacEr_set_tile_x_y();
	
	int id = RacEr_x_y_to_id(RacEr_x,RacEr_y);

       
	//if( (RacEr_x < RACER_TILE_GROUP_X_DIM) && (RacEr_y < RACER_TILE_GROUP_Y_DIM) ){
	if(  (RacEr_x>= BARRIER_X_START  && RacEr_x <= BARRIER_X_END) && (RacEr_y>= BARRIER_Y_START  && RacEr_y <= BARRIER_Y_END)   ){
	
		int local_var[64];
		

        //----------------------------------------------------------------
        //1. Setup shared memory.
        //----------------------------------------------------------------
	RacEr_tile_group_shared_mem(int, shared_mem, 67);

		
        //----------------------------------------------------------------
        //2. Initialize elements 0-15 of tilegroup-shared memory 
		//   Each tile stores its id to sh_mem[(id+2)%16] (which is in local memory of two tiles ahead)
		//    Store to Shared Mem
        //----------------------------------------------------------------
	RacEr_tile_group_shared_store(int, shared_mem,((id+2)%16),id);
				
        //----------------------------------------------------------------
        //3. Sync the group
        //----------------------------------------------------------------
        RacEr_tile_group_barrier(&row_barrier_inst, &col_barrier_inst);
  //      RacEr_printf( "I am here\n") ;

        //----------------------------------------------------------------
        //4. Each tile loads the first 16 elements of shared memory into local memory 	
        //----------------------------------------------------------------		
	for (int idx = 0; idx < 16 ; idx ++ )
		RacEr_tile_group_shared_load(int, shared_mem,idx,local_var[idx]);
		

        //----------------------------------------------------------------
        //5. Sync the group
        //----------------------------------------------------------------		
        RacEr_tile_group_barrier(&row_barrier_inst, &col_barrier_inst);

		
        //----------------------------------------------------------------
        //6. Check print
        //----------------------------------------------------------------			
	if ( id == 0)
	{
		for ( int idx = 0; idx < 16 ; idx ++)
			RacEr_printf( "Check Print:\tsh_mem[%d] = %d\n" , idx , local_var[idx]) ;
      }
		
        //----------------------------------------------------------------
        //7. Sync the group
        //----------------------------------------------------------------			
        RacEr_tile_group_barrier(&row_barrier_inst, &col_barrier_inst);

        //----------------------------------------------------------------
        //8. Tile 0 finished the execution
        //----------------------------------------------------------------
	if( id == 0) 
		RacEr_finish();
	}

	RacEr_wait_while(1);
}

