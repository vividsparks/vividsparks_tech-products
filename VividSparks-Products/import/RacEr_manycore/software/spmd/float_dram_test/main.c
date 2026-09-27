#include "RacEr_manycore.h"
#include "RacEr_set_tile_x_y.h"
#include <math.h>
#define address 0x80000000
#define N 10000
int main()
{
  int *read_address;
  int i;  
  RacEr_set_tile_x_y();
if ((__RacEr_x == 0) && (__RacEr_y == 0))
  {
    for (i=0; i<=N;  i++) {
    read_address = (int*)address;  
    read_address = read_address + i;
    if (*read_address==0xDEEDCEEF) RacEr_printf("val is correct\n");

    //RacEr_printf("address= %p\n", read_address);
    //*read_address = 0xDEADBEEF;
    //RacEr_printf("address val= %x\n", *read_address);
    }

    RacEr_finish();
}

  RacEr_wait_while(1);
}
