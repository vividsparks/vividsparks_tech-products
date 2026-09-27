#define N 256
#include <math.h>
#include "RacEr_manycore.h"
#include "RacEr_set_tile_x_y.h"

#define hex(X) (*(int*)&X)

float vecA[N]; 
float vecB[N];

int main()
{

  RacEr_set_tile_x_y();

  // initialize
  for (int i = 0; i < N; i++)
  {
    vecA[i] = (float) i;
    vecB[i] = (float) i;
  }


  RacEr_cuda_print_stat_start(0);
  float dp = 0.0f;
  #pragma GCC unroll 4
  for (int i = 0; i < N; i++)
  {
    dp += vecA[i] * vecB[i];
  }
  RacEr_cuda_print_stat_end(0);
  
  RacEr_printf("expected = 4aa9ab00\n");
  RacEr_printf("actual   = %x\n", hex(dp));

  if (hex(dp) == 0x4aa9ab00)
    RacEr_finish();
  else
    RacEr_fail();

  RacEr_wait_while(1);
}
